#include "backendgp.h"

#include <qdebug.h>

BackendGP::BackendGP(QObject *parent) : QObject(parent)
{

}

void BackendGP::motor_setState(int newMotor_State)
{
    if(_Motor_State != newMotor_State) {
        _Motor_State = newMotor_State;
        emit motor_stateChanged();
    }
}



void BackendGP::gp_setState(int newGP_State)
{
    if(_GP_State != newGP_State) {
        _GP_State = newGP_State;
        emit gp_stateChanged();
    }
}

