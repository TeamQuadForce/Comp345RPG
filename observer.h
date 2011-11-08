#ifndef OBSERVER_H
#define OBSERVER_H
#include "playercharacter.h"

class Observable;

class Observer
{
public:
    virtual void update(Observable *aObserved) = 0;
};

#endif // OBSERVER_H
