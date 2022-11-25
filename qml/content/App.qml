/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick Studio Components.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.Window
import atv_dashboard


Window {
    id: root
    width: 1920
    height: 1080

    visible: true
    title: "Vector ATV Clutch Dashboard"

    visibility: "FullScreen"



    Mainform {
    }


    Item {
        id: backend
        property real x_angle: 0.0
        property real y_angle: 0.0
        property real z_angle: 0.0
        property real to_x_angle: 0.0
        property real to_y_angle: 0.0
        property real to_z_angle: 0.0


        property SequentialAnimation model_x_turning:
        SequentialAnimation {
            loops: -1
            running: false


            PropertyAnimation {
                target: backend;
                property: "x_angle";

                to: backend.to_x_angle
                duration: 2000
            }

        }

        property SequentialAnimation model_y_turning:

        SequentialAnimation {
            loops: -1
            running: false


            PropertyAnimation {
                target: backend;
                property: "y_angle";

                to: backend.to_y_angle
                duration: 2000
            }

        }




    }


}

