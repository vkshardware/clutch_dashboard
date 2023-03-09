#ifndef CANBUSPROCESS_H
#define CANBUSPROCESS_H

#include <QCanBus>
#include <QCanBusFrame>
#include <QCloseEvent>
#include <QDateTime>
#include <QDesktopServices>
#include <QLabel>
#include <QTimer>
#include <QString>

#include "controllerdata.h"

#define PCB1_ID 0x11
#define PCB2_ID 0x12
#define CONNECTION_LOST 6

QT_BEGIN_NAMESPACE

class QCanBusFrame;
class QLabel;
class QTimer;

namespace Ui {
class CanbusProcess;
}

QT_END_NAMESPACE


class CanbusProcess : public QObject
{
    Q_OBJECT

public:
    explicit CanbusProcess(QWidget *parent = nullptr);
    ~CanbusProcess() override;

    ControllerData pcb1, pcb2;
    void initActionsConnections();
    bool link_established = false;
    bool AnimationEnable = true;


private slots:
    void processReceivedFrames();
    void sendFrame(const QCanBusFrame &frame) const;
    void processErrors(QCanBusDevice::CanBusError) const;
    void connectDevice();
    void busStatus();
    void disconnectDevice();
    void processFramesWritten(qint64);
    void onAppendFramesTimeout();


private:
    qint64 m_numberFramesWritten = 0;
    qint64 m_numberFramesReceived = 0;
    Ui::CanbusProcess *m_ui = nullptr;
    std::unique_ptr<QCanBusDevice> m_canDevice;
    QTimer *m_busStatusTimer = nullptr;
    QTimer *m_appendTimer = nullptr;
    QTimer *is_connected = nullptr;

    QString deviceInterfaceName = "can0";

    QString pluginName = "socketcan";
    void ConnectionCheck();

};


#endif // CANBUSPROCESS_H
