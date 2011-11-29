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
#include "logger.h"

PlayGenerator::PlayGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayGenerator)
{
    ui->setupUi(this);
    connect(ui->loadCharacterButton, SIGNAL(clicked()), SLOT(loadCharacter()));
    connect(ui->loadMapButton, SIGNAL(clicked()), SLOT(loadMap()));
    connect(ui->enterDungeonButton, SIGNAL(clicked()), SLOT(enterDungeon()));
    connect(ui->backButton, SIGNAL(clicked()), SLOT(backToMainScreen()));

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
    short level;
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
    level = in.readLine().toShort();
    strength = in.readLine().toShort();
    dexterity = in.readLine().toShort();
    constitution = in.readLine().toShort();
    intelligence = in.readLine().toShort();
    wisdom = in.readLine().toShort();
    charisma = in.readLine().toShort();
    filename= in.readLine();
    file.close();

    mPlayer = new PlayerCharacter(name,gender,race,className);
    mPlayer->modifyAbilityScores(strength,dexterity,constitution,intelligence,wisdom,charisma);
    mPlayer->init();

    for(int i=1; i<level; i++){
        mPlayer->levelUp();
    }
}

void PlayGenerator::enterDungeon()
{
    if (mPlayer != 0 && mMap != 0)
    {
        Game *game = (Game*)this->parentWidget();
        Dungeon *dungeon = new Dungeon((Game*)this->parentWidget());
        dungeon->init(mPlayer, mMap, filename);
        game->insertWidget(4, dungeon);
        game->setCurrentIndex(4);

    }
}

void PlayGenerator::backToMainScreen(){
    Game *game=(Game*)this->parentWidget();
    game->setCurrentIndex(0);
}
