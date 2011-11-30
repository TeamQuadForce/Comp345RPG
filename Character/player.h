#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
class Player{
public:
    virtual short attack(QString &message) = 0;
    virtual short rollInitiative(QString &message) = 0;
    virtual QString type() = 0;

};

#endif // PLAYER_H
