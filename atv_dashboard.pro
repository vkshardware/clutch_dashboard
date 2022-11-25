QT += quickcontrols2 widgets

SOURCES += \
        dashboard.cpp \
        main.cpp

resources.files = main.qml

resources.prefix = /$${TARGET}

CONFIG += qmltypes
QML_IMPORT_NAME = io.qt.examples.backendq
QML_IMPORT_MAJOR_VERSION = 1

RESOURCES += \
    $$files(qml/*)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =  /qml/imports/atv_dashboard


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = /qml

HEADERS += \
    dashboard.h
