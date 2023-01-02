/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import Data 1.0 as Data
import "functions.js" as FR

Item {
    id: motor

    width: 60
    height: 60

    property int motor_state: 0


    Image {
        id: motorfree
        anchors.verticalCenter: parent.verticalCenter
        source: "icons/motor_off.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: motorup
        anchors.verticalCenter: parent.verticalCenter
        source: "icons/motor_up.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: motordown
        anchors.verticalCenter: parent.verticalCenter
        source: "icons/motor_down.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: motorholdon
        anchors.verticalCenter: parent.verticalCenter
        source: "icons/motor_holdon.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    states: [
        State {
            name: "free"
            when: motor_state == 0

            PropertyChanges {
                target: motorfree
                visible: true
            }

            PropertyChanges {
                target: motorup
                visible: false
            }

            PropertyChanges {
                target: motordown
                visible: false
            }

            PropertyChanges {
                target: motorholdon
                visible: false
            }



        },
        State {
            name: "up"
            when: motor_state == 1


            PropertyChanges {
                target: motorfree
                visible: false
            }

            PropertyChanges {
                target: motorup
                visible: true
            }

            PropertyChanges {
                target: motordown
                visible: false
            }

            PropertyChanges {
                target: motorholdon
                visible: false
            }


        },

        State {
            name: "down"
            when: motor_state == 2



            PropertyChanges {
                target: motorfree
                visible: false
            }

            PropertyChanges {
                target: motorup
                visible: false
            }

            PropertyChanges {
                target: motordown
                visible: true
            }

            PropertyChanges {
                target: motorholdon
                visible: false
            }


        },

        State {
            name: "holdon"
            when: motor_state == 3


            PropertyChanges {
                target: motorfree
                visible: false
            }

            PropertyChanges {
                target: motorup
                visible: false
            }

            PropertyChanges {
                target: motordown
                visible: false
            }

            PropertyChanges {
                target: motorholdon
                visible: true
            }
        }

    ]
}
