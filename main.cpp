#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickStyle>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <QtQml>
#include "dashboard.h"
#include "iconblock.h"
#include "backendgp.h"


int main(int argc, char *argv[])
{


    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QGuiApplication app(argc, argv);


    QQuickStyle::setStyle("Universal");

    QQmlApplicationEngine engine;

    BackendGP front_left_GP, rear_left_GP, front_right_GP, rear_right_GP;
    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Front_left_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return &front_left_GP;
    });

    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Rear_left_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return &rear_left_GP;
    });

    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Front_right_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return &front_right_GP;
    });

    qmlRegisterSingletonType<BackendGP>("org.vks.GPObjects", 1, 0, "Rear_right_GP",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return &rear_right_GP;
    });

    front_left_GP.motor_setState(1);

    IconBlock iconblock;

    qmlRegisterSingletonType<IconBlock>("org.vks.GPObjects", 1, 0, "IconBlock",
                                     [&](QQmlEngine *, QJSEngine *) -> QObject * {
        return &iconblock;
    });

    iconblock.gp_link_setstate(true);



    const QUrl url(u"qrc:/qml/content/App.qml"_qs);

    engine.addImportPath("qrc:/qml/imports/");
    engine.addImportPath("qrc:/qml/asset_imports/");





    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.load(url);


    return app.exec();


}
