#ifndef GENERICMONSTER_H
#define GENERICMONSTER_H

#include <QString>
#include "observable.h"
#include "observer.h"
#include "player.h"

class Monster : public Observable, public Player
{
public:
    Monster();
    Monster(const QString &aName);
    virtual ~Monster();

    short rollHitDie();
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
    QString name();    

    void modifyAbilityScores(short aStrength, short aDexterity,
                             short aConstitution, short aIntelligence,
                             short aWisdom, short aCharisma);

    void setHitPoints(short numOfDice, short typeOfDice, short modifier);
    void modifyAttack(short aAttackRolls, short aAttackDice, short aAttackModifier);
    void modifyStats(short aBaseArmorClass, short aBaseAttack, short aLevel);

    short abilityScore(AbilityScore aAbilityName);
    short abilityModifier(AbilityScore aAbilityName);
    short meleeAttackBonus(int aAttackNumber);
    short rangedAttackBonus(int aAttackNumber);
    short hitPoints();
    short armorClass();
    short level();
    short attack(QString &message);
    short rollInitiative(QString &message);

    //Observer methods
    void addObserver(Observer *aObserver);
    void removeObserver(Observer *aObserver);
    void notifyObservers();

private:
    void setStartingItems();

    QList<Observer*> mObserverList;
    QString mName;

    short mBaseAttack;
    short mAttackRolls;
    short mAttackDice;
    short mAttackModifier;
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

#endif // GENERICMONSTER_H
