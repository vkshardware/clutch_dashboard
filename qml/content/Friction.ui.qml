import QtQuick 2.8
import QtQuick.Layouts 1.0
import QtQuick.Studio.Components 1.0

Item {
    id: friction

    width: 44
    height: 85
    property int fric_state: 0

    state: "normal"
    Image {
        id: frictionfree
        anchors.verticalCenter: parent.verticalCenter
        source: "frictions/friction_free.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: frictiondown
        anchors.verticalCenter: parent.verticalCenter
        source: "frictions/friction_down_sw.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: frictionup
        anchors.verticalCenter: parent.verticalCenter
        source: "frictions/friction_up_sw.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: frictionfault
        anchors.verticalCenter: parent.verticalCenter
        source: "frictions/friction_fault.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    states: [
        State {
            name: "free"
            when: fric_state == 0

            PropertyChanges {
                target: frictionfree
                visible: true
            }

            PropertyChanges {
                target: frictiondown
                visible: false
            }

            PropertyChanges {
                target: frictionup
                visible: false
            }

            PropertyChanges {
                target: frictionfault
                visible: false
            }
        },
        State {
            name: "down"
            when: fric_state == 1


            PropertyChanges {
                target: frictionfree
                visible: false
            }

            PropertyChanges {
                target: frictiondown
                visible: true
            }

            PropertyChanges {
                target: frictionup
                visible: false
            }

            PropertyChanges {
                target: frictionfault
                visible: false
            }
        },

        State {
            name: "up"
            when: fric_state == 2


            PropertyChanges {
                target: frictionfree
                visible: false
            }

            PropertyChanges {
                target: frictiondown
                visible: false
            }

            PropertyChanges {
                target: frictionup
                visible: true
            }

            PropertyChanges {
                target: frictionfault
                visible: false
            }
        },

        State {
            name: "fault"
            when: fric_state == 3


            PropertyChanges {
                target: frictionfree
                visible: false
            }

            PropertyChanges {
                target: frictiondown
                visible: false
            }

            PropertyChanges {
                target: frictionup
                visible: false
            }

            PropertyChanges {
                target: frictionfault
                visible: true
            }
        }
    ]
}
