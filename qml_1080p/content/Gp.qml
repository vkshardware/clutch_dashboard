import QtQuick 2.8
import QtQuick.Layouts 1.0
import QtQuick.Studio.Components 1.0
import Data 1.0 as Data

Item {
    id: gp
    width: 506
    height: 588

    Image {
        id: logo1
        x: 0
        y: 0
        source: "carLogo1.png"
    }

    Motor {
        id: gpfront_left_channel_on_Icon
        x: 155
        y: 3
        motor_state: Data.Values.front_left_Motor_state
    }

    Motor {
        id: gpfront_right_channel_on_Icon
        x: 289
        y: 3
        motor_state: Data.Values.front_right_Motor_state
    }

    Motor {
        id: gprear_left_channel_on_Icon
        x: 156
        y: 525
        motor_state: Data.Values.rear_left_Motor_state
    }

    Motor {
        id: gprear_right_channel_on_Icon
        x: 292
        y: 526
        motor_state: Data.Values.rear_right_Motor_state
    }

    Friction {
        id: rearGP_left
        x: 163
        y: 445
        fric_state: Data.Values.rear_left_GP_state
    }

    Friction {
        id: frontGP_left
        x: 164
        y: 61
        fric_state: Data.Values.front_left_GP_state
    }

    Friction {
        id: rearGP_right
        x: 299
        y: 446
        fric_state: Data.Values.rear_right_GP_state
    }

    Friction {
        id: frontGP_right
        x: 300
        y: 61
        fric_state: Data.Values.front_right_GP_state
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/
