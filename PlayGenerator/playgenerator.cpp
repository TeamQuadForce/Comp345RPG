#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QDateTime>
#include <QLayout>
#include <QDebug>
#include <QFileDialog>
#include "playgenerator.h"
#include "ui_playgenerator.h"
#include "map.h"
#include "game.h"
#include "dungeon.h"

PlayGenerator::PlayGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayGenerator)
{
    ui->setupUi(this);
    connect(ui->loadCharacterButton, SIGNAL(clicked()), SLOT(loadCharacter()));
    connect(ui->loadMapButton, SIGNAL(clicked()), SLOT(loadMap()));
    connect(ui->enterDungeonButton, SIGNAL(clicked()), SLOT(enterDungeon()));

    mPlayer = 0;
    mMap = 0;
}

PlayGenerator::~PlayGenerator()
{
    delete ui;
    delete mMap;
    delete mPlayer;
}

void PlayGenerator::loadMap(){

    mMap = new Map();
    mMap->loadMap();
}

void PlayGenerator::loadCharacter(){

    QString race;
    QString className;
    QString gender;
    QString name;
    short strength;
    short dexterity;
    short constitution;
    short intelligence;
    short wisdom;
    short charisma;

    QString fileName = QFileDialog::getOpenFileName();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    race = in.readLine();
    className = in.readLine();
    gender = in.readLine();
    name = in.readLine();
    strength = in.readLine().toShort();
    dexterity = in.readLine().toShort();
    constitution = in.readLine().toShort();
    intelligence = in.readLine().toShort();
    wisdom = in.readLine().toShort();
    charisma = in.readLine().toShort();
    file.close();

    mPlayer = new PlayerCharacter(name,gender,race,className);
    mPlayer->modifyAbilityScores(strength,dexterity,constitution,intelligence,wisdom,charisma);
}

void PlayGenerator::enterDungeon()
{
    if (mPlayer != 0 && mMap != 0)
    {
        Game *game = (Game*)this->parentWidget();
        Dungeon *dungeon = new Dungeon((Game*)this->parentWidget());
        dungeon->init(mPlayer, mMap);
        game->insertWidget(4, dungeon);
        game->setCurrentIndex(4);
    }
}
