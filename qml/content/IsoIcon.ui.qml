import QtQuick 2.8
import QtQuick.Layouts 1.0
import QtQuick.Studio.Components 1.0


Item {
    id: isoIcon
    property alias iconOffSource: iconOff.source
    property alias iconOnSource: iconOn.source
   width: 100 //92
   height: 70 //64
    property bool active: false
    state: "normal"
    Image {
        id: iconOff
        anchors.verticalCenter: parent.verticalCenter
        source: "icons/gp_fault_off.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: iconOn
        x: 0
        y: 0
        anchors.verticalCenter: parent.verticalCenter
        source: "icons/gp_fault_on.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "normal"
            when: !isoIcon.active

            PropertyChanges {
                target: iconOn
                visible: false
            }

            PropertyChanges {
                target: iconOff
                visible: true
            }

            PropertyChanges {
                target: isoIcon
                visible: true
            }
        },
        State {
            name: "active"
            when: isoIcon.active

            PropertyChanges {
                target: iconOff
                visible: false
            }

            PropertyChanges {
                target: iconOn
                visible: true
            }

            PropertyChanges {
                target: isoIcon
                visible: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:61.1875;width:61.1875}
}
##^##*/
