#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <QString>
#include <QPixmap>
#include "characterclass.h"
#include "inventory.h"
#include "observable.h"
#include "observer.h"

class PlayerCharacter : public Observable
{
public:
    PlayerCharacter();
    PlayerCharacter(const QString &aName, const QString &aGender, const QString &aRace, const QString &aClassName, QPixmapData *aPortrait = 0);
    virtual ~PlayerCharacter();

    enum AbilityScore
    {
        Strength = 0,
        Dexterity,
        Constitution,
        Intelligence,
        Wisdom,
        Charisma
    };

    void init();
    void levelUp();
    CharacterClass * characterClass();
    QString race();
    QString className();
    QString gender();
    QString name();
    QPixmap portrait();

    void modifyAbilityScores(short aStrength, short aDexterity,
                             short aConstitution, short aIntelligence,
                             short aWisdom, short aCharisma);

    short abilityScore(AbilityScore aAbilityName);
    short abilityModifier(AbilityScore aAbilityName);
    short meleeAttackBonus(int aAttackNumber);
    short rangedAttackBonus(int aAttackNumber);
    short hitPoints();
    short armorClass();
    short level();

    //Observer methods
    void addObserver(Observer *aObserver);
    void removeObserver(Observer *aObserver);
    void notifyObservers();

private:
    QList<Observer*> mObserverList;
    CharacterClass *mClass;
    Inventory mInventory;

    QString mRace;
    QString mClassName;
    QString mGender;
    QString mName;

    QPixmap mPortrait;

    short mHitPoints;
    short mBaseArmorClass;
    short mLevel;

    //Ability scores
    short mStrength;
    short mDexterity;
    short mConstitution;
    short mIntelligence;
    short mWisdom;
    short mCharisma;
};

#endif // PLAYERCHARACTER_H
