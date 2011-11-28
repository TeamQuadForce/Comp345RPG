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
        Armor,
        Ring
    };

    Item();
    Item(const QString &aItemName, const ItemType &aItemType);

    QString itemName();
    ItemType itemType();
    void setEquipped(bool aEquip);
    bool isEquipped();

protected:
    QString mItemName;
    ItemType mItemType;
    bool mIsEquipped;
};

#endif // ITEM_H
