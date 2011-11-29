#ifndef MONSTERREPERTOIRE_H
#define MONSTERREPERTOIRE_H

#include <QList>
#include "genericmonster.h"

class MonsterRepertoire
{
public:
    virtual ~MonsterRepertoire();
    static MonsterRepertoire* getUniqueInstance();
    GenericMonster* getRandomMonster();
    GenericMonster * getMonster(short aLevel);

private:
    MonsterRepertoire();
    void fillRepertoire();

    static MonsterRepertoire* mMonsterRepertoire;
    QList<GenericMonster*> mMonsterList;
};

#endif // MONSTERREPERTOIRE_H
