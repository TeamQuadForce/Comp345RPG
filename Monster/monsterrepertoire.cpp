#include "monsterrepertoire.h"

MonsterRepertoire* MonsterRepertoire::mMonsterRepertoire = 0;

MonsterRepertoire::MonsterRepertoire()
{
    mMonsterList.clear();
}

MonsterRepertoire::~MonsterRepertoire()
{
    qDeleteAll(mMonsterList);
}

MonsterRepertoire* MonsterRepertoire::getUniqueInstance()
{
    if (mMonsterRepertoire == 0)
    {
        mMonsterRepertoire = new MonsterRepertoire;
        mMonsterRepertoire->fillRepertoire();
    }

    return mMonsterRepertoire;
}

//fills the repertoire with hard coded Monsters of different levels
//monsters taken from http://www.monsteradvancer.com/
void MonsterRepertoire::fillRepertoire()
{
    Monster* level1 = new Monster("Badger");
    level1->modifyStats(15, 0, 1);
    level1->setHitPoints(1, 8 , 2);
    level1->modifyAttack(1, 2, -1);
    level1->modifyAbilityScores(8, 17, 15, 2, 12, 6);

    Monster* level2 = new Monster("Azer");
    level2->modifyStats(17, 2, 2);
    level2->setHitPoints(2, 8, 2);
    level2->modifyAttack(1, 8, 1);
    level2->modifyAbilityScores(13, 13, 13, 12, 12, 9);

    Monster* level3 = new Monster("Camel");
    level3->modifyStats(13, 3, 3);
    level3->setHitPoints(3, 8, 6);
    level3->modifyAttack(1, 4, 0);
    level3->modifyAbilityScores(18, 16, 14, 2, 11, 4);

    Monster* level4 = new Monster("Centaur");
    level4->modifyStats(14, 4, 4);
    level4->setHitPoints(4, 8, 8);
    level4->modifyAttack(2, 6, 4);
    level4->modifyAbilityScores(18, 14, 15, 8, 13, 11);

    Monster* level5 = new Monster("Bison");
    level5->modifyStats(13, 3, 5);
    level5->setHitPoints(5, 8, 15);
    level5->modifyAttack(1, 8, 9);
    level5->modifyAbilityScores(22, 10, 16, 2, 11, 4);

    Monster* level6 = new Monster("Basilisk");
    level6->modifyStats(16, 6, 6);
    level6->setHitPoints(6, 10, 12);
    level6->modifyAttack(1, 8, 3);
    level6->modifyAbilityScores(15, 8, 15, 2, 12, 11);

    Monster* level7 = new Monster("Belker");
    level7->modifyStats(22, 5, 7);
    level7->setHitPoints(7, 8, 7);
    level7->modifyAttack(1, 6, 2);
    level7->modifyAbilityScores(14, 21, 13, 6, 11, 11);

    Monster* level8 = new Monster("Aboleth");
    level8->modifyStats(16, 6, 8);
    level8->setHitPoints(8, 8, 40);
    level8->modifyAttack(1, 6, 8);
    level8->modifyAbilityScores(26, 12, 20, 15, 17, 17);

    Monster* level9 = new Monster("Bodak");
    level9->modifyStats(20, 4, 9);
    level9->setHitPoints(9, 12, 0);
    level9->modifyAttack(1, 8, 1);
    level9->modifyAbilityScores(13, 15, 1, 6, 12, 12);

    Monster* level10 = new Monster("Black Pudding");
    level10->modifyStats(3, 7, 10);
    level10->setHitPoints(10, 10, 60);
    level10->modifyAttack(2, 6, 4);
    level10->modifyAbilityScores(17, 1, 22, 1, 1, 1);

    Monster* level11 = new Monster("Young Black Dragon");
    level11->modifyStats(19, 11, 11);
    level11->setHitPoints(11, 12, 22);
    level11->modifyAttack(1, 8 ,2);
    level11->modifyAbilityScores(15, 10, 15, 10, 11, 10);

    Monster* level12 = new Monster("Androsphinx");
    level12->modifyStats(22, 12, 12);
    level12->setHitPoints(12, 10, 48);
    level12->modifyAttack(2, 4, 7);
    level12->modifyAbilityScores(25, 10, 19, 16, 17, 17);

    Monster* level13 = new Monster("Juvenile Black Dragon");
    level13->modifyStats(22, 13, 13);
    level13->setHitPoints(13, 12, 26);
    level13->modifyAttack(1, 8, 3);
    level13->modifyAbilityScores(17, 10, 15, 10, 11, 10);

    Monster* level14 = new Monster("Large Bodak");
    level14->modifyStats(20, 7, 14);
    level14->setHitPoints(14, 12, 0);
    level14->modifyAttack(2, 6, 5);
    level14->modifyAbilityScores(21, 13, 1, 6, 12, 12);

    Monster* level15 = new Monster("Baleen Whale");
    level15->modifyStats(16, 11, 15);
    level15->setHitPoints(15, 8, 93);
    level15->modifyAttack(1, 8, 18);
    level15->modifyAbilityScores(35, 13, 22, 2, 12, 6);

    Monster* level16 = new Monster("Huge Chimera");
    level16->modifyStats(20, 16, 16);
    level16->setHitPoints(16, 10, 80);
    level16->modifyAttack(3, 6, 8);
    level16->modifyAbilityScores(27, 11, 21, 4, 13, 10);

    Monster* level17 = new Monster("Gargantuan Behir");
    level17->modifyStats(22, 17, 17);
    level17->setHitPoints(17, 10, 119);
    level17->modifyAttack(2, 6, 18);
    level17->modifyAbilityScores(34, 13, 25, 7, 14, 12);

    Monster* level18 = new Monster("Abyssal Greater Basilisk");
    level18->modifyStats(17, 18, 18);
    level18->setHitPoints(18, 8, 90);
    level18->modifyAttack(3, 8, 10);
    level18->modifyAbilityScores(24, 8, 21, 3, 10, 15);

    Monster* level19 = new Monster("Astral Deva Angel");
    level19->modifyStats(29, 19, 19);
    level19->setHitPoints(19, 8, 114);
    level19->modifyAttack(2, 6, 18);
    level19->modifyAbilityScores(30, 16, 22, 18, 18, 20);

    Monster* level20 = new Monster("Planetar Angel");
    level20->modifyStats(32, 20, 20);
    level20->setHitPoints(20, 8, 100);
    level20->modifyAttack(3, 6, 13);
    level20->modifyAbilityScores(25, 19, 20, 22, 23, 22);

    mMonsterList.append(level1);
    mMonsterList.append(level2);
    mMonsterList.append(level3);
    mMonsterList.append(level4);
    mMonsterList.append(level5);
    mMonsterList.append(level6);
    mMonsterList.append(level7);
    mMonsterList.append(level8);
    mMonsterList.append(level9);
    mMonsterList.append(level10);
    mMonsterList.append(level11);
    mMonsterList.append(level12);
    mMonsterList.append(level13);
    mMonsterList.append(level14);
    mMonsterList.append(level15);
    mMonsterList.append(level16);
    mMonsterList.append(level17);
    mMonsterList.append(level18);
    mMonsterList.append(level19);
    mMonsterList.append(level20);
}

Monster * MonsterRepertoire::getMonster(short aLevel)
{
    //make a list containing all the Monsters that a character this level can have

    foreach(Monster* monster, mMonsterList)
    {
        if (monster->level() == aLevel)
        {
            return monster;
        }
    }

    //Return a random Monster from this level list
    return getRandomMonster();
}

Monster * MonsterRepertoire::getRandomMonster()
{
    return mMonsterList[qrand() % mMonsterList.size()];
}
