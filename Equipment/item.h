#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
public:
    enum ItemType
    {
        Potion = 0,
        Weapon,
        Armor
    };

    Item();
    Item(const QString &aItemName, const ItemType &aItemType);

    QString itemName();
    ItemType itemType();
    void setEquipped(bool aEquip);
    bool isEquipped();
    unsigned short level();

    //virtual QString itemDescription() = 0;

protected:
    QString mItemName;
    ItemType mItemType;
    bool mIsEquipped;
    unsigned short mLevel;
};

#endif // ITEM_H
