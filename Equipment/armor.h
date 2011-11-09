#ifndef ARMOR_H
#define ARMOR_H
#include "item.h"

class Armor : public Item
{
public:
    enum ArmorType
    {
        BodyArmor = 0,
        Gloves,
        Helmet,
        Boots,
        Belt
    };

    Armor();
    Armor(const QString &aItemName, const ArmorType &aArmorType);

    ArmorType armorType();

private:
    short mArmorClass;
    ArmorType mArmorType;
};

#endif // ARMOR_H
