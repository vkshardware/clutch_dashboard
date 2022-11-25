QT += quickcontrols2 widgets

SOURCES += \
        backendgp.cpp \
        dashboard.cpp \
        iconblock.cpp \
        main.cpp

resources.files = main.qml

resources.prefix = /$${TARGET}

CONFIG += qmltypes
    QML_IMPORT_NAME = org.vks.GPObjectType
    QML_IMPORT_MAJOR_VERSION = 1

RESOURCES += \
    $$files(qml/*)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =  /qml/imports/atv_dashboard


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = /qml

HEADERS += \
    backendgp.h \
    dashboard.h \
    iconblock.h
