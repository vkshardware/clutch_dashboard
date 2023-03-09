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
        x: 105
        y: 1
        motor_state: Data.Values.front_left_Motor_state
    }

    Motor {
        id: gpfront_right_channel_on_Icon
        x: 212
        y: 0
        motor_state: Data.Values.front_right_Motor_state
    }

    Motor {
        id: gprear_left_channel_on_Icon
        x: 105
        y: 420
        motor_state: Data.Values.rear_left_Motor_state
    }

    Motor {
        id: gprear_right_channel_on_Icon
        x: 216
        y: 420
        motor_state: Data.Values.rear_right_Motor_state
    }

    Friction {
        id: rearGP_left
        x: 112
        y: 340
        fric_state: Data.Values.rear_left_GP_state
    }

    Friction {
        id: frontGP_left
        x: 112
        y: 54
        fric_state: Data.Values.front_left_GP_state
    }

    Friction {
        id: rearGP_right
        x: 225
        y: 340
        fric_state: Data.Values.rear_right_GP_state
    }

    Friction {
        id: frontGP_right
        x: 225
        y: 55
        fric_state: Data.Values.front_right_GP_state
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/
