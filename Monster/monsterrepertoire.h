#ifndef MONSTERREPERTOIRE_H
#define MONSTERREPERTOIRE_H

#include <QList>
#include "monster.h"

class MonsterRepertoire
{
public:
    virtual ~MonsterRepertoire();
    static MonsterRepertoire* getUniqueInstance();
    Monster* getRandomMonster();
    Monster * getMonster(short aLevel);

private:
    MonsterRepertoire();
    void fillRepertoire();

    static MonsterRepertoire* mMonsterRepertoire;
    QList<Monster*> mMonsterList;
};

#endif // MONSTERREPERTOIRE_H
