#ifndef OBSERVER_H
#define OBSERVER_H
#include "playercharacter.h"

//Forward declarations
class PlayerCharacter;

class Observer
{
public:
    virtual void update(PlayerCharacter *aPlayer) = 0;
};

#endif // OBSERVER_H
