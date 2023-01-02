#ifndef ANIMATION_H
#define ANIMATION_H
#include <QObject>

class AnimationATV : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int angle READ angle_get NOTIFY angle_changed)
    Q_PROPERTY(bool run READ run_getstate NOTIFY run_changed)

public:
    explicit AnimationATV(QObject *parent = nullptr);

    Q_INVOKABLE int angle_get() { return _angle; }

    void angle_set(int newstate);
    int _angle = 0;

    //faultF2
    Q_INVOKABLE bool run_getstate() { return _run; }
    void run_setstate(bool newstate);
    bool _run= false;

signals:
    void angle_changed();
    void run_changed();

public slots:


private:

};
#endif // ANIMATION_H
