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
    Weapon(const QString &aItemName, const WeaponType &aWeaponType);

    WeaponType weaponType();
    unsigned short range();
    unsigned short numOfDice();
    unsigned short damageDie();
    unsigned short numOfHandsToWield();

private:
    WeaponType mWeaponType;
    unsigned short mRange;
    unsigned short mNumberOfDamageDice;
    unsigned short mDamageDie;
    unsigned short mNumberOfHandsToWield;
};

#endif // WEAPON_H
