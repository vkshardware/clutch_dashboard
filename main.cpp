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


int main(int argc, char *argv[])
{


    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QGuiApplication app(argc, argv);


    QQuickStyle::setStyle("Universal");

    QQmlApplicationEngine engine;



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
