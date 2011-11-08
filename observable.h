#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "observer.h"

class Observer;

class Observable
{
    virtual void addObserver(Observer *aObserver) = 0;
    virtual void removeObserver(Observer *aObserver) = 0;
    virtual void notifyObservers() = 0;
};

#endif // OBSERVABLE_H
