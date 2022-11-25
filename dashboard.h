#ifndef DASHBOARD
#define DASHBOARD



#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QSettings>
#include <QtQml>

struct parameter{
    char name[32];
    uint8_t def_value;
    uint8_t min_value;
    uint8_t max_value;
    uint8_t point_pos;
    uint8_t actual_value;
    bool writable;
};

struct display_data{
    char name[32];
    uint8_t byte;
    uint8_t bit_number;
    uint8_t actual_value;
};

#define MSG_COUNT_DISPLAY 21
#define MSG_COUNT_PARAMETER 40


class Example_class : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:

    qint32 One();
    void setOne(qint32 value);


};

class Dashboard : public QObject
{
    Q_OBJECT
public:
    Dashboard();
    QTcpSocket *tcpSocket = nullptr;
    QSettings settings;
    QString ConstructDisplayMessage();
    void LoadDisplayMessage(QString src);

    parameter parameters[MSG_COUNT_PARAMETER] =  {{"WAIT_SEC_UP",9,3,100,1,0,true},
                                                  {"WAIT_SEC_DOWN",20,3,100,1,0,true},
                                                  {"WAIT_MOVING_UP_STOP",10,0,100,0,0,true},
                                                  {"JOYSTICK_PERSENTAGE_L",0,0,0,0,0,false},
                                                  {"CMD_L",0,0,0,1,0,false},
                                                  {"JOYSTICK_ENABLE_L",0,0,0,0,0,false},
                                                  {"JOYSTICK_PERSENTAGE_R",0,0,0,0,0,false},
                                                  {"CMD_R",0,0,0,1,0,false},
                                                  {"JOYSTICK_ENABLE_R",0,0,0,0,0,false},
                                                  {"JOYSTICK_L_BOTTOM_LIMIT",10,0,99,0,0,true},
                                                  {"JOYSTICK_L_4_STEP",25,0,99,0,0,true},
                                                  {"JOYSTICK_L_3_STEP",30,0,99,0,0,true},
                                                  {"JOYSTICK_L_2_STEP",35,0,99,0,0,true},
                                                  {"JOYSTICK_L_1_STEP",40,0,99,0,0,true},
                                                  {"JOYSTICK_L_1_STEP_RESERVE",61,0,99,0,0,true},
                                                  {"JOYSTICK_L_2_STEP_RESERVE",66,0,99,0,0,true},
                                                  {"JOYSTICK_L_3_STEP_RESERVE",71,0,99,0,0,true},
                                                  {"JOYSTICK_L_4_STEP_RESERVE",76,0,99,0,0,true},
                                                  {"JOYSTICK_L_TOP_LIMIT",90,0,99,0,0,true},
                                                  {"JOYSTICK_R_BOTTOM_LIMIT",10,0,99,0,0,true},
                                                  {"JOYSTICK_R_4_STEP",25,0,99,0,0,true},
                                                  {"JOYSTICK_R_3_STEP",30,0,99,0,0,true},
                                                  {"JOYSTICK_R_2_STEP",35,0,99,0,0,true},
                                                  {"JOYSTICK_R_1_STEP",40,0,99,0,0,true},
                                                  {"JOYSTICK_R_1_STEP_RESERVE",61,0,99,0,0,true},
                                                  {"JOYSTICK_R_2_STEP_RESERVE",66,0,99,0,0,true},
                                                  {"JOYSTICK_R_3_STEP_RESERVE",71,0,99,0,0,true},
                                                  {"JOYSTICK_R_4_STEP_RESERVE",76,0,99,0,0,true},
                                                  {"JOYSTICK_R_TOP_LIMIT",90,0,99,0,0,true},
                                                  {"CURRENT_JAM_PROTECT_L_F1",10,1,50,0,0,true},
                                                  {"TIME_JAM_PROTECT_L_F1",10,1,99,2,0,true},
                                                  {"CURRENT_JAM_PROTECT_R_F1",10,1,50,0,0,true},
                                                  {"TIME_JAM_PROTECT_R_F1",10,1,99,2,0,true},
                                                  {"OVERCURRENT_PROTECT_L_F2",45,0,80,0,0,true},
                                                  {"OVERCURRENT_PROTECT_R_F2",45,0,80,0,0,true},
                                                  {"HOLD_ON_UNDERLOAD_L",0,0,10,0,0,true},
                                                  {"HOLD_ON_UNDERLOAD_R",0,0,10,0,0,true},
                                                  {"ACTUATOR_SPEED_NORMAL_MODE",10,1,10,0,0,true},
                                                  {"ACTUATOR_SPEED_WATER_MODE",4,1,10,0,0,true},
                                                  {"BOTH_SIDES_RELEASE_LOGIC",0,0,1,0,0,true}};
    display_data display[MSG_COUNT_DISPLAY] =    {{"STATUS_BIT0_L_ON",0,0,0},
                                                  {"STATUS_BIT0_R_ON",0,1,0},
                                                  {"STATUS_BIT0_L_D",0,2,0},
                                                  {"STATUS_BIT0_L_U",0,3,0},
                                                  {"STATUS_BIT0_R_D",0,4,0},
                                                  {"STATUS_BIT0_R_U",0,5,0},
                                                  {"STATUS_BIT0_L_BUT",0,6,0},
                                                  {"STATUS_BIT0_R_BUT",0,7,0},
                                                  {"STATUS_BIT1_L_EN",1,0,0},
                                                  {"STATUS_BIT1_R_EN",1,1,0},
                                                  {"STATUS_BIT1_L_ON_U",1,2,0},
                                                  {"STATUS_BIT1_L_ON_D",1,3,0},
                                                  {"STATUS_BIT1_R_ON_U",1,4,0},
                                                  {"STATUS_BIT1_R_ON_D",1,5,0},
                                                  {"STATUS_BIT1_L_TRIP_STAGE1",1,6,0}, //L TRIP current protection jamming
                                                  {"STATUS_BIT1_R_TRIP_STAGE1",1,7,0}, //R TRIP current protection jamming
                                                  {"STATUS_BIT2_L_TRIP_STAGE2",2,0,0}, //L TRIP over current protection short circuit
                                                  {"STATUS_BIT2_R_TRIP_STAGE2",2,1,0}, //R TRIP over current protection short circuit
                                                  {"STATUS_BIT2_WATERMODE",2,2,0},     //Water mode
                                                  {"STATUS_BIT2_SQUEEZE",2,3,0},        //Release both sides
                                                  {"STATUS_BIT2_HOLD_ON_LOAD",2,4,0}};  //hold drive under load


public slots:
    void cppSlot();
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);


private:
    QDataStream in;
    QString currentFortune;


};

#endif // Dashboard
