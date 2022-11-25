#ifndef BackendGP_H
#define BackendGP_H


#include <QObject>

class BackendGP : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int motor_state READ motor_getState NOTIFY motor_stateChanged)
    Q_PROPERTY(int gp_state READ gp_getState NOTIFY gp_stateChanged)

public:
    explicit BackendGP(QObject *parent = nullptr);

    Q_INVOKABLE int motor_getState() { return _Motor_State; }
    Q_INVOKABLE int gp_getState() { return _GP_State; }

    void motor_setState(int newstate);
    int _Motor_State = 0;

    void gp_setState(int newstate);
    int _GP_State = 0;

signals:
    void motor_stateChanged();
    void gp_stateChanged();

public slots:


private:

};

#endif // BackendGP_H
