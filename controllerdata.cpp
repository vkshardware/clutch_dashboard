#include <QtWidgets>
#include <controllerdata.h>



ControllerData::ControllerData(QWidget *parent)
    :     QObject(parent)
{
 //*
}




bool ControllerData::LoadDisplayMessage(QString src)
{
    static QRegularExpression rx("[ ]");  // match a space
    QStringList list = src.split(rx);
    bool ok = false;

    if (list.size() >= 8)
    {
        data[0] = QString(list.value(0)).toUInt(&ok,16);
        data[1] = QString(list.value(1)).toUInt(&ok,16);
        data[2] = QString(list.value(2)).toUInt(&ok,16);
    }

    for (int i=0;i<8;i++)
    {
        display[i].actual_value = data[0] & (1 << display[i].bit_number); //fill status byte 0
        display[i+8].actual_value = data[1] & (1 << display[i+8].bit_number); //fill status byte 1
    }

    for (int i=0;i<5;i++)
    {
        display[i+16].actual_value = data[2] & (1 << display[i+16].bit_number); //fill status byte 2
    }



    return ok;
}




