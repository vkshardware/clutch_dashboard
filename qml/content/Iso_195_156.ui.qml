

/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Design Studio.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
import QtQuick 2.8
import QtQuick.Layouts 1.0
import QtQuick.Studio.Components 1.0
import Data 1.0 as Data


Item {
    id: iso_195_156
    width: 700
    height: 68

    Image {
        id: iso_195_156Asset
        x: 0
        y: 0
        width: 700
        height: 68
        source: "assets/iso_195_156.png"
    }

    RowLayout {
        x: -60
        y: 4
        scale: 0.8
        spacing: 20

        IsoIcon {
            id: gpConnectionIcon
            x: 0
            y: 0
            active: Data.Values.gplink
            iconOffSource: "icons/gp_no_link.png"
            iconOnSource: "icons/gp_link.png"
        }

        IsoIcon {
            id: waterIcon
            x: 0
            y: 0
            active: Data.Values.water
            iconOffSource: "icons/water_off.png"
            iconOnSource: "icons/water_on.png"
        }

        IsoIcon {
            id: holdonIcon
            x: 0
            y: 0
            active: Data.Values.holdon
            iconOffSource: "icons/holdon_off.png"
            iconOnSource: "icons/holdon_on.png"
        }

        IsoIcon {
            id: rearGPIcon
            x: 0
            y: 0
            active: Data.Values.rearGP_squeeze
            iconOffSource: "icons/rear_gp_off.png"
            iconOnSource: "icons/rear_gp_on.png"
        }

        IsoIcon {
            id: frontGPIcon
            x: 0
            y: 0
            active: Data.Values.frontGP_squeeze
            iconOffSource: "icons/front_gp_off.png"
            iconOnSource: "icons/front_gp_on.png"
        }

        IsoIcon {
            id: faultF1Icon
            x: 0
            y: 0
            active: Data.Values.faultF1
            iconOffSource: "icons/f1_off.png"
            iconOnSource: "icons/f1_on.png"
        }

        IsoIcon {
            id: faultF2Icon
            x: 0
            y: 0
            active: Data.Values.faultF2
            iconOffSource: "icons/f2_off.png"
            iconOnSource: "icons/f2_on.png"
        }
    }
}



