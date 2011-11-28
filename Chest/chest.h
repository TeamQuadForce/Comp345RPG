#ifndef CHEST_H
#define CHEST_H

#include "item.h"
#include <QList>

class Chest
{
public:
    Chest();
    void addItems();

private:
    QList<Item*> mItemList;
};

#endif // CHEST_H
