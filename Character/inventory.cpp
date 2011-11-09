#include "inventory.h"
#include <QDebug>
#include "weapon.h"
#include "armor.h"

Inventory::Inventory()
{
}

void Inventory::addItem(Item *aItem)
{
    mBackpack.append(aItem);
}

void Inventory::removeItem(const int &aIndex)
{
    mBackpack.removeAt(aIndex);
}

void Inventory::equipItem(const int &aIndex)
{
    mEquippedItems.insert(aIndex, mBackpack[aIndex]);
}

void Inventory::unequipItem(const int &aIndex)
{
    mEquippedItems.removeAt(aIndex);
}

QList<Item*> Inventory::equippedItems()
{
    return mEquippedItems;
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
