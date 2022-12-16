#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "backendgp.h"
#include "iconblock.h"
#include "canbusprocess.h"
#include <QTimer>

CanbusProcess * can0;
IconBlock * iconblock;
BackendGP * front_left_GP;
BackendGP * rear_left_GP;
BackendGP * front_right_GP;
BackendGP * rear_right_GP;

void update_data()
{

    iconblock->gp_link_setstate(can0->link_established);

    iconblock->water_setstate(can0->pcb1.display[18].actual_value || can0->pcb2.display[18].actual_value );
    iconblock->holdon_setstate(can0->pcb1.display[20].actual_value || can0->pcb2.display[20].actual_value );
    iconblock->rearGP_squeeze_setstate(can0->pcb1.display[19].actual_value);
    iconblock->frontGP_squeeze_setstate(can0->pcb2.display[19].actual_value);
    iconblock->faultF1_setstate(can0->pcb1.display[14].actual_value || can0->pcb1.display[15].actual_value ||
                               can0->pcb2.display[14].actual_value || can0->pcb2.display[15].actual_value);

    iconblock->faultF2_setstate(can0->pcb1.display[16].actual_value || can0->pcb1.display[17].actual_value ||
                                can0->pcb2.display[17].actual_value || can0->pcb2.display[17].actual_value);

    //Set motor states
    if (can0->pcb1.display[10].actual_value) rear_left_GP->motor_setState(1);
    if (can0->pcb1.display[11].actual_value) rear_left_GP->motor_setState(2);
    if (!(can0->pcb1.display[10].actual_value && can0->pcb1.display[11].actual_value)) rear_left_GP->motor_setState(0);

    if (can0->pcb1.display[12].actual_value) rear_right_GP->motor_setState(1);
    if (can0->pcb1.display[13].actual_value) rear_right_GP->motor_setState(2);
    if (!(can0->pcb1.display[12].actual_value && can0->pcb1.display[13].actual_value)) rear_right_GP->motor_setState(0);

    if (can0->pcb2.display[10].actual_value) front_left_GP->motor_setState(1);
    if (can0->pcb2.display[11].actual_value) front_left_GP->motor_setState(2);
    if (!(can0->pcb2.display[10].actual_value && can0->pcb2.display[11].actual_value)) front_left_GP->motor_setState(0);

    if (can0->pcb2.display[12].actual_value) front_right_GP->motor_setState(1);
    if (can0->pcb2.display[13].actual_value) front_right_GP->motor_setState(2);
    if (!(can0->pcb2.display[12].actual_value && can0->pcb2.display[13].actual_value)) front_right_GP->motor_setState(0);

    //Set GP states

    if (can0->pcb1.display[2].actual_value) rear_left_GP->gp_setState(1);
    if (can0->pcb1.display[3].actual_value) rear_left_GP->gp_setState(2);
    if (!(can0->pcb1.display[2].actual_value && can0->pcb1.display[3].actual_value)) rear_left_GP->gp_setState(0);
    if (can0->pcb1.display[14].actual_value || can0->pcb1.display[16].actual_value) rear_left_GP->gp_setState(3);

    if (can0->pcb1.display[4].actual_value) rear_right_GP->gp_setState(1);
    if (can0->pcb1.display[5].actual_value) rear_right_GP->gp_setState(2);
    if (!(can0->pcb1.display[4].actual_value && can0->pcb1.display[5].actual_value)) rear_right_GP->gp_setState(0);
    if (can0->pcb1.display[15].actual_value || can0->pcb1.display[17].actual_value) rear_right_GP->gp_setState(3);

    if (can0->pcb2.display[2].actual_value) front_left_GP->gp_setState(1);
    if (can0->pcb2.display[3].actual_value) front_left_GP->gp_setState(2);
    if (!(can0->pcb2.display[2].actual_value && can0->pcb2.display[3].actual_value)) front_left_GP->gp_setState(0);
    if (can0->pcb2.display[14].actual_value || can0->pcb2.display[16].actual_value) front_left_GP->gp_setState(3);

    if (can0->pcb2.display[4].actual_value) front_right_GP->gp_setState(1);
    if (can0->pcb2.display[5].actual_value) front_right_GP->gp_setState(2);
    if (!(can0->pcb2.display[4].actual_value && can0->pcb2.display[5].actual_value)) front_right_GP->gp_setState(0);
    if (can0->pcb2.display[15].actual_value || can0->pcb2.display[16].actual_value) front_right_GP->gp_setState(3);
}


int main(int argc, char *argv[])
{
    QTimer *updateTimer = nullptr;

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QGuiApplication app(argc, argv);


    QQuickStyle::setStyle("Universal");

    QQmlApplicationEngine engine;

    front_left_GP = new BackendGP();
    front_right_GP = new BackendGP();
    rear_left_GP = new BackendGP();
    rear_right_GP = new BackendGP();

    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Front_left_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return front_left_GP;
    });

    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Rear_left_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return rear_left_GP;
    });

    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Front_right_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return front_right_GP;
    });

    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Rear_right_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return rear_right_GP;
    });



    iconblock = new IconBlock();

    qmlRegisterSingletonType<IconBlock>("org.vks.GPObjects", 1, 0, "IconBlock",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return iconblock;
    });





    const QUrl url(u"qrc:/qml/content/App.qml"_qs);

    engine.addImportPath("qrc:/qml/imports/");
    engine.addImportPath("qrc:/qml/asset_imports/");





    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.load(url);

    can0 = new CanbusProcess();
    can0->initActionsConnections();

    updateTimer = new QTimer();
    QObject::connect(updateTimer, &QTimer::timeout, &app, &update_data);
    updateTimer->start(200);

    return app.exec();


}
