#include "animation.h"

#include <qdebug.h>

AnimationATV::AnimationATV(QObject *parent) : QObject(parent)
{

}

void AnimationATV::angle_set(int newstate)
{
    if(_angle != newstate) {
        _angle = newstate;
        emit angle_changed();
    }
}

void AnimationATV::run_setstate(bool newstate)
{
    if(_run != newstate) {
        _run = newstate;
        emit run_changed();
    }
}
