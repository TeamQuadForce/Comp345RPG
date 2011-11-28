#ifndef ITEMREPERTOIRE_H
#define ITEMREPERTOIRE_H

#include "item.h"
#include <QList>

class ItemRepertoire
{
public:
    virtual ~ItemRepertoire();
    static ItemRepertoire* getUniqueInstance();

    Item* getItem(unsigned short aLevel);
    Item* getRandomItem();

private:
    ItemRepertoire();
    void fillRepertoire();

    static ItemRepertoire* mItemRepertoire;
    QList<Item*> mItemList;
};

#endif // ITEMREPERTOIRE_H
