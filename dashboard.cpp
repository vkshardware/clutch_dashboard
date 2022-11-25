#include <QtWidgets>
#include <QSettings>
#include <dashboard.h>



Dashboard::Dashboard()
    : tcpSocket(new QTcpSocket(this))
{
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    connect(tcpSocket, &QIODevice::readyRead, this, &Dashboard::readFortune);

    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &Dashboard::displayError);
}

void Dashboard::cppSlot()
{
    qDebug()<<"Trying";


    requestNewFortune();
}

void Example_class::setOne(qint32 value)
{
    qDebug()<<value;
}

QString Dashboard::ConstructDisplayMessage()
{
    QString result;

    for (int i=0; i<MSG_COUNT_DISPLAY;i++)
    {
       result = result + display[i].name+"="+QString::number(display[i].actual_value)+",";
    }

    return result;
}

void Dashboard::LoadDisplayMessage(QString src)
{
    static QRegularExpression rx("[,=]");  // match a comma or a space
    QStringList list = src.split(rx);

    int k = 0;


    for (int i=0; i < list.size(); i++)
    {
        if (i % 2 > 0)
        {
                if (k < MSG_COUNT_DISPLAY)
                   display[k].actual_value = list.value(i).toInt();
                k++;
        }

    }
}

void Dashboard::requestNewFortune()
{

    QSettings settings(QApplication::applicationDirPath()+"/config/settings.ini",QSettings::NativeFormat);
    QString server_ip;
    int server_port;

    server_ip = settings.value("SERVER_IP").toString();
    server_port = settings.value("SERVER_PORT").toInt();

    if (server_ip == "")
    {
        settings.setValue("SERVER_IP", "localhost");
        server_ip = settings.value("SERVER_IP").toString();
    }

    if (server_port == 0)
    {
        settings.setValue("SERVER_PORT", "3333");
        server_port = settings.value("SERVER_PORT").toInt();
    }

    tcpSocket->abort();
//! [7]
    tcpSocket->connectToHost(server_ip, server_port);
//! [7]
}


void Dashboard::readFortune()
{
    QString buff;
    in.startTransaction();

    in >> buff;

    if (!in.commitTransaction())
        return;

/*    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, &Dashboard::requestNewFortune);
        return;
    }

    currentFortune = nextFortune; */

    qDebug().noquote() << buff;
    LoadDisplayMessage(buff);


}

void Dashboard::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "Not Found";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "Refused";
        break;
    default:
        qDebug() << tcpSocket->errorString();
    }


}
