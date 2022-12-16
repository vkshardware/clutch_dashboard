
#include <QCanBus>
#include <QCanBusFrame>
#include <QCloseEvent>
#include <QDateTime>
#include <QDesktopServices>
#include <QLabel>
#include <QTimer>
#include <QSettings>
#include <QtWidgets>
#include "canbusprocess.h"
#include "controllerdata.h"

CanbusProcess::CanbusProcess(QWidget *parent) :
    QObject(parent),
    m_busStatusTimer(new QTimer(this))
{
    QSettings settings(QApplication::applicationDirPath()+"/config/settings.ini",QSettings::NativeFormat);

    bool ok = false;

    pcb1.controller_id = QString(settings.value("PCB1_ID").toString()).toUInt(&ok, 16);
    pcb2.controller_id = QString(settings.value("PCB2_ID").toString()).toUInt(&ok, 16);

    if (pcb1.controller_id == 0)
    {
        settings.setValue("PCB1_ID", "0x11");
        pcb1.controller_id = PCB1_ID;
    }

    if (pcb2.controller_id == 0)
    {
        settings.setValue("PCB2_ID", "0x12");
        pcb2.controller_id = PCB2_ID;
    }

    deviceInterfaceName = settings.value("INTERFACE_NAME").toString();
    if (deviceInterfaceName == "") deviceInterfaceName = "vcan0";

    pluginName = settings.value("PLUGIN_NAME").toString();
    if (pluginName == "") pluginName = "socketcan";

    connect(m_busStatusTimer, &QTimer::timeout, this, &CanbusProcess::busStatus);

    m_appendTimer = new QTimer(this);
    connect(m_appendTimer, &QTimer::timeout, this, &CanbusProcess::onAppendFramesTimeout);
   // m_appendTimer->start(200);

    is_connected = new QTimer(this);
    connect(is_connected, &QTimer::timeout, this, &CanbusProcess::ConnectionCheck);
    is_connected->start(500);


}

CanbusProcess::~CanbusProcess()
{
 //
}

void CanbusProcess::initActionsConnections()
{
    connectDevice();
}

void CanbusProcess::processErrors(QCanBusDevice::CanBusError error) const
{
    switch (error) {
    case QCanBusDevice::ReadError:
    case QCanBusDevice::WriteError:
    case QCanBusDevice::ConnectionError:
    case QCanBusDevice::ConfigurationError:
    case QCanBusDevice::UnknownError:
        qDebug() << m_canDevice->errorString()+" "+deviceInterfaceName;
        break;
    default:
        break;
    }
}

void CanbusProcess::connectDevice()
{

    QString errorString;
    m_canDevice.reset(QCanBus::instance()->createDevice(pluginName, deviceInterfaceName,
                                                        &errorString));
    if (!m_canDevice) {
        qDebug() << "Error creating device '%1', reason: '%2'" + pluginName + errorString;

        return;
    }

    m_numberFramesWritten = 0;

    connect(m_canDevice.get(), &QCanBusDevice::errorOccurred,
            this, &CanbusProcess::processErrors);
    connect(m_canDevice.get(), &QCanBusDevice::framesReceived,
            this, &CanbusProcess::processReceivedFrames);
    connect(m_canDevice.get(), &QCanBusDevice::framesWritten,
            this, &CanbusProcess::processFramesWritten);

    if (!m_canDevice->connectDevice()) {
       qDebug() << (tr("Connection error: %1").arg(m_canDevice->errorString()));

        m_canDevice.reset();
    } else {


        const QVariant bitRate = m_canDevice->configurationParameter(QCanBusDevice::BitRateKey);
        if (bitRate.isValid()) {
            const bool isCanFd =
                    m_canDevice->configurationParameter(QCanBusDevice::CanFdKey).toBool();
            const QVariant dataBitRate =
                    m_canDevice->configurationParameter(QCanBusDevice::DataBitRateKey);
            if (isCanFd && dataBitRate.isValid()) {
                qDebug() << (tr("Plugin: %1, connected to %2 at %3 / %4 kBit/s")
                                  .arg(pluginName).arg(deviceInterfaceName)
                                  .arg(bitRate.toInt() / 1000).arg(dataBitRate.toInt() / 1000));
            } else {
                qDebug() << (tr("Plugin: %1, connected to %2 at %3 kBit/s")
                                  .arg(pluginName).arg(deviceInterfaceName)
                                  .arg(bitRate.toInt() / 1000));
            }
        } else {
            qDebug() << (tr("Plugin: %1, connected to %2")
                    .arg(pluginName).arg(deviceInterfaceName));
        }

        if (m_canDevice->hasBusStatus())
            m_busStatusTimer->start(2000);
        else
            qDebug() << tr("No CAN bus status available.");
    }
}

void CanbusProcess::busStatus()
{
    if (!m_canDevice || !m_canDevice->hasBusStatus()) {
        qDebug() << (tr("No CAN bus status available."));
        m_busStatusTimer->stop();
        return;
    }

    switch (m_canDevice->busStatus()) {
    case QCanBusDevice::CanBusStatus::Good:
        qDebug() << ("CAN bus status: Good.");
        break;
    case QCanBusDevice::CanBusStatus::Warning:
        qDebug() << ("CAN bus status: Warning.");
        break;
    case QCanBusDevice::CanBusStatus::Error:
        qDebug() << ("CAN bus status: Error.");
        break;
    case QCanBusDevice::CanBusStatus::BusOff:
        qDebug() << ("CAN bus status: Bus Off.");
        break;
    default:
        qDebug() << ("CAN bus status: Unknown.");
        break;
    }
}

void CanbusProcess::disconnectDevice()
{
    if (!m_canDevice)
        return;

    m_busStatusTimer->stop();

    m_canDevice->disconnectDevice();

    qDebug() << ("Disconnected");
}

void CanbusProcess::processFramesWritten(qint64 count)
{
    m_numberFramesWritten += count;

}

static QString frameFlags(const QCanBusFrame &frame)
{
    QString result = QLatin1String(" --- ");

    if (frame.hasBitrateSwitch())
        result[1] = QLatin1Char('B');
    if (frame.hasErrorStateIndicator())
        result[2] = QLatin1Char('E');
    if (frame.hasLocalEcho())
        result[3] = QLatin1Char('L');

    return result;
}

void CanbusProcess::processReceivedFrames()
{
    if (!m_canDevice)
        return;


    while (m_canDevice->framesAvailable()) {
        m_numberFramesReceived++;
        const QCanBusFrame frame = m_canDevice->readFrame();

        QString data;
        if (frame.frameType() == QCanBusFrame::ErrorFrame)
            data = m_canDevice->interpretErrorFrame(frame);
        else
            data = QLatin1String(frame.payload().toHex(' ').toUpper());

        const QString time = QString::fromLatin1("%1.%2  ")
                .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));

        const QString flags = frameFlags(frame);

        const QString id = QString::number(frame.frameId(), 16);

        const QString dlc = QString::number(frame.payload().size());




        if (pcb1.controller_id == frame.frameId())
        {
            pcb1.LoadDisplayMessage(data);
            pcb1.connection_timer = 0;
        }
        if (pcb2.controller_id == frame.frameId())
        {
            pcb2.LoadDisplayMessage(data);
            pcb2.connection_timer = 0;
        }


        qDebug() << QString(time +flags+id+dlc+data);


    }
}

void CanbusProcess::sendFrame(const QCanBusFrame &frame) const
{
    if (!m_canDevice)
        return;

    m_canDevice->writeFrame(frame);
}

void CanbusProcess::onAppendFramesTimeout()
{
    if (!m_canDevice)
        return;

        qDebug().nospace() << tr("%1 frames received ").arg(m_numberFramesReceived);

}

void CanbusProcess::ConnectionCheck()
{
    link_established = !((pcb1.connection_timer > CONNECTION_LOST) || (pcb2.connection_timer > CONNECTION_LOST));

    pcb1.connection_timer++;
    pcb2.connection_timer++;

}

