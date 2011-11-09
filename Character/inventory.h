#ifndef INVENTORY_H
#define INVENTORY_H

#include <QList>
#include "observable.h"
#include "item.h"

class Inventory : public Observable
{
public:
    Inventory();

    void addObserver(Observer *aObserver);
    void removeObserver(Observer *aObserver);
    void notifyObservers();

    void addItem(Item* aItem);
    void removeItem(const int &aIndex);
    void equipItem(const int &aIndex);
    void unequipItem(const int &aIndex);
    QList<Item*> equippedItems();

private:
    QList<Item*> mEquippedItems;
    QList<Item*> mBackpack;
    QList<Observer*> mObserverList;
};

#endif // INVENTORY_H
