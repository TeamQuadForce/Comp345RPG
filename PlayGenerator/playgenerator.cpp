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

PlayGenerator::PlayGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayGenerator)
{
    ui->setupUi(this);
    connect(ui->loadCharacterButton, SIGNAL(clicked()), SLOT(loadCharacter()));
    connect(ui->loadMapButton, SIGNAL(clicked()), SLOT(loadMap()));
}

PlayGenerator::~PlayGenerator()
{
    delete ui;
}
void PlayGenerator::loadMap(){

    map = new Map();
    map->loadMap();

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
