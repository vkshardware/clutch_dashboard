#ifndef ICONBLOCK_H
#define ICONBLOCK_H



#include <QObject>

class IconBlock : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool gp_link READ gp_link_getstate NOTIFY gp_link_changed)
    Q_PROPERTY(bool water READ water_getstate NOTIFY water_changed)
    Q_PROPERTY(bool holdon READ holdon_getstate NOTIFY holdon_changed)
    Q_PROPERTY(bool rearGP_squeeze READ rearGP_squeeze_getstate NOTIFY rearGP_squeeze_changed)
    Q_PROPERTY(bool frontGP_squeeze READ frontGP_squeeze_getstate NOTIFY frontGP_squeeze_changed)
    Q_PROPERTY(bool faultF1 READ faultF1_getstate NOTIFY faultF1_changed)
    Q_PROPERTY(bool faultF2 READ faultF2_getstate NOTIFY faultF2_changed)

public:
    explicit IconBlock(QObject *parent = nullptr);
    //gp_link
    Q_INVOKABLE bool gp_link_getstate() { return _gp_link; }
    void gp_link_setstate(bool newstate);
    bool _gp_link = false;

    //water
    Q_INVOKABLE bool water_getstate() { return _water; }
    void water_setstate(bool newstate);
    bool _water = false;

    //holdon
    Q_INVOKABLE bool holdon_getstate() { return _holdon; }
    void holdon_setstate(bool newstate);
    bool _holdon = false;

    //rearGP_squeeze
    Q_INVOKABLE bool rearGP_squeeze_getstate() { return _rearGP_squeeze; }
    void rearGP_squeeze_setstate(bool newstate);
    bool _rearGP_squeeze= false;

    //frontGP_squeeze
    Q_INVOKABLE bool frontGP_squeeze_getstate() { return _frontGP_squeeze; }
    void frontGP_squeeze_setstate(bool newstate);
    bool _frontGP_squeeze = false;

    //faultF1
    Q_INVOKABLE bool faultF1_getstate() { return _faultF1; }
    void faultF1_setstate(bool newstate);
    bool _faultF1 = false;

    //faultF2
    Q_INVOKABLE bool faultF2_getstate() { return _faultF2; }
    void faultF2_setstate(bool newstate);
    bool _faultF2 = false;

signals:
    void gp_link_changed();
    void water_changed();
    void holdon_changed();
    void rearGP_squeeze_changed();
    void frontGP_squeeze_changed();
    void faultF1_changed();
    void faultF2_changed();
};


#endif // ICONBLOCK_H
