#include "inventory.h"

Inventory::Inventory()
{
}

void Inventory::addObserver(Observer *aObserver)
{
    if (!mObserverList.contains(aObserver))
    {
        mObserverList.append(aObserver);
    }
}

void Inventory::removeObserver(Observer *aObserver)
{
    if (mObserverList.contains(aObserver))
    {
        mObserverList.removeOne(aObserver);
    }
}

void Inventory::notifyObservers()
{
    foreach(Observer *obs, mObserverList)
    {
        obs->update(this);
    }
}
