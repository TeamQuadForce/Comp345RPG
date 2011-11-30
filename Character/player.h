#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "logger.h"

class Player{
public:
    virtual short attack(Logger* aLogger) = 0;
    virtual short rollInitiative(Logger* aLogger) = 0;
    virtual QString type() = 0;
    virtual bool takeDamage(short aDamage) = 0;
    virtual short rollHit(Logger* aLogger) = 0;
};

#endif // PLAYER_H
