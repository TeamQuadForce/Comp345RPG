#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "observer.h"
#include <Qlist>

class Observer;

//Classes should inherit this if they need to be observed by a list of observers
class Observable
{
public:
    virtual void addObserver(Observer *aObserver) = 0;
    virtual void removeObserver(Observer *aObserver) = 0;
    virtual void notifyObservers() = 0;

    QList<Observer *> mObserverList;
};

#endif // OBSERVABLE_H
