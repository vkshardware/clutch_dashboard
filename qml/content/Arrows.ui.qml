/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import atv_dashboard
import "functions.js" as FR
import Data 1.0 as Data

Item {

    width: 360
    height: 60

    Image {
        source: "icons/arrow_left.png"
        x: 0
        y: 0


        MouseArea {
            id: arrow_left
            anchors.fill: parent
        }
    }


    Image {
        source: "icons/arrow_right.png"
        x: 100
        y: 0

        MouseArea {
            id: arrow_right
            anchors.fill: parent
        }
    }

    Image {
        source: "icons/arrow_up.png"
        x: 200
        y: 0

        MouseArea {
            id: arrow_up
            anchors.fill: parent
        }
    }

    Image {
        source: "icons/arrow_down.png"
        x: 300
        y: 0

        MouseArea {
            id: arrow_down
            anchors.fill: parent
        }
    }


    Connections {
        target: arrow_left
        function onPressed() {
            FR.rotateLeft()
        }
    }

    Connections {
        target: arrow_left
        function onReleased() {
            backend.running = false
            backend.duration = 700
            backend.to_y_angle = 0
        }
    }

    Connections {
        target: arrow_right
        function onPressed() {
            FR.rotateRight()
        }
    }

    Connections {
        target: arrow_right
        function onReleased() {
            backend.running = false
            backend.duration = 700
            backend.to_y_angle = 0
        }
    }

    Connections {
        target: arrow_up
        function onPressed() {
            FR.rotateUp()
        }
    }

    Connections {
        target: arrow_up
        function onReleased() {
            backend.model_x_turning.running = false
        }
    }

    Connections {
        target: arrow_down
        function onPressed() {
            FR.rotateDown()
        }
    }

    Connections {
        target: arrow_down
        function onReleased() {
            backend.model_x_turning.running = false
        }
    }

}
