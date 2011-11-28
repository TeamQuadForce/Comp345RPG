#ifndef INVENTORY_H
#define INVENTORY_H

#include <QList>
#include "item.h"
//class Item;

class Inventory
{
public:
    Inventory();

    void addItem(Item* aItem);
    void removeItem(const int &aIndex);
    void equipItem(const int &aIndex);
    void unequipItem(const int &aIndex);
    QList<Item*> backpack();

private:
    QList<Item*> mBackpack;
};

#endif // INVENTORY_H
