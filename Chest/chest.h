#ifndef CHEST_H
#define CHEST_H

#include "item.h"
#include <QList>

class Chest
{
public:
    Chest();
    Chest(int aLevel);
    QList<Item*>& itemList();
    int level();

private:
    QList<Item*> mItemList;
    int mLevel;
};

#endif // CHEST_H
