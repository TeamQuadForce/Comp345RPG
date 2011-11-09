#ifndef INVENTORY_H
#define INVENTORY_H

#include <QList>
#include "observable.h"
#include "item.h"

class Inventory : public Observable
{
public:
    Inventory();

    void addItem(const Item &aItem);
    void removeItem(const int &aIndex);
    void equipItem(const int &aIndex);
    void unequipItem(const int &aIndex);

    void addObserver(Observer *aObserver);
    void removeObserver(Observer *aObserver);
    void notifyObservers();

private:
    QList<Item> mEquippedItems;
    QList<Item> mBackpack;
    QList<Observer*> mObserverList;
};

#endif // INVENTORY_H
