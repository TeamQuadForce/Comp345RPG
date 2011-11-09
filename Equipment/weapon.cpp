#include "weapon.h"

Weapon::Weapon()
{
}

Weapon::Weapon(const QString &aItemName, const WeaponType &aWeaponType) :
    mWeaponType(aWeaponType)
{
    Item::Item(aItemName, Item::Weapon);
}

Weapon::WeaponType Weapon::weaponType()
{
    return mWeaponType;
}

unsigned short Weapon::range()
{
    return mRange;
}

unsigned short Weapon::numOfDice()
{
    return mNumberOfDamageDice;
}

unsigned short Weapon::damageDie()
{
    return mDamageDie;
}

unsigned short Weapon::numOfHandsToWield()
{
    return mNumberOfHandsToWield;
}
