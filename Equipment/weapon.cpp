#include "weapon.h"

Weapon::Weapon()
{
}

Weapon::Weapon(const QString &aItemName, const WeaponType &aWeaponType,
               const unsigned short &aRange, const unsigned short &aNumOfDamageDice,
               const unsigned short &aDamageDie, const short &aMagicalDamageBonus,
               const unsigned short &aNumOfHands) :
    mWeaponType(aWeaponType),
    mRange(aRange),
    mNumberOfDamageDice(aNumOfDamageDice),
    mDamageDie(aDamageDie),
    mMagicalDamageBonus(aMagicalDamageBonus),
    mNumberOfHandsToWield(aNumOfHands)
{
    mItemName = aItemName;
    mItemType = Item::Weapon;
    mIsEquipped = false;
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

QString Weapon::itemDescription()
{
    return QString("%1 (%2d%3)").arg(mItemName).arg(mNumberOfDamageDice).arg(mDamageDie);
}
