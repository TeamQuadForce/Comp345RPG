#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item
{
public:
    enum WeaponType
    {
        Melee = 0,
        Ranged
    };

    Weapon();
    Weapon(const QString &aItemName, const WeaponType &aWeaponType, const unsigned short &aRange,
           const unsigned short &aNumOfDamageDice, const unsigned short &aDamageDie,
           const unsigned short &aNumOfHands);

    WeaponType weaponType();
    unsigned short range();
    unsigned short numOfDice();
    unsigned short damageDie();
    unsigned short numOfHandsToWield();

    QString itemDescription();

private:
    WeaponType mWeaponType;
    unsigned short mRange;
    unsigned short mNumberOfDamageDice;
    unsigned short mDamageDie;
    unsigned short mNumberOfHandsToWield;
};

#endif // WEAPON_H
