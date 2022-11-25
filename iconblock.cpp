#include <qdebug.h>
#include "iconblock.h"

IconBlock::IconBlock(QObject *parent) : QObject(parent)
{

}

void IconBlock::gp_link_setstate(bool newstate)
{
    if(_gp_link != newstate) {
        _gp_link = newstate;
        emit gp_link_changed();
    }
}

void IconBlock::water_setstate(bool newstate)
{
    if(_water != newstate) {
        _water = newstate;
        emit water_changed();
    }
}

void IconBlock::holdon_setstate(bool newstate)
{
    if(_holdon != newstate) {
        _holdon = newstate;
        emit holdon_changed();
    }
}

void IconBlock::rearGP_squeeze_setstate(bool newstate)
{
    if(_rearGP_squeeze != newstate) {
        _rearGP_squeeze = newstate;
        emit rearGP_squeeze_changed();
    }
}

void IconBlock::frontGP_squeeze_setstate(bool newstate)
{
    if(_frontGP_squeeze != newstate) {
        _frontGP_squeeze = newstate;
        emit frontGP_squeeze_changed();
    }
}

void IconBlock::faultF1_setstate(bool newstate)
{
    if(_faultF1 != newstate) {
        _faultF1= newstate;
        emit faultF1_changed();
    }
}

void IconBlock::faultF2_setstate(bool newstate)
{
    if(_faultF2 != newstate) {
        _faultF2 = newstate;
        emit faultF2_changed();
    }
}
