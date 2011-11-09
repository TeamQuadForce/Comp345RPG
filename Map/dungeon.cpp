#include "dungeon.h"
#include "ui_dungeon.h"
#include <QFileDialog>

Dungeon::Dungeon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dungeon)
{
    ui->setupUi(this);
    init();
}

Dungeon::~Dungeon()
{
    delete ui;
}

void Dungeon::init()
{
    mapObject = new Map();
    mapObject->loadMap();
    initializeMap();
    this->show();
}


//Method it initialize the map
void Dungeon::initializeMap()
{
    //Implement Matt Tam's "createMap" stuff
}

//Method to assignment operations to movement buttons
void Dungeon::assignMovementOperations()
{
    connect(ui->movementButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(moveCharacter(QAbstractButton*)));
}

//Slot to move the character
void Dungeon::moveCharacter(QAbstractButton* button)
{
    mapObject->moveCharacter(button->text());
}

void Dungeon::update(Observable *aObs)
{
//    QIcon characterImage(":/images/fighter.jpg");
//    QIcon wallImage(":/images/wall.jpg");
//    QIcon enemyImage(":/images/enemy.jpg");
//    QIcon exitImage(":/images/exit.jpg");
//    QIcon chestImage(":/images/chest.jpg");
//    QIcon terrainImage(":/images/terrain.jpg");

    Map *aMap = (Map*)aObs;
    TileSet tile = aMap->lastModifiedTileSet();
    int row = tile.rowPosition();
    int column = tile.columnPosition();

    if(tile.getGamePiece().compare("Character") == 0)
    {
        mapGrid[row][column]->setStyleSheet("background-color: blue;");
    }
    else
    {
        mapGrid[row][column]->setStyleSheet("background-color: white;");
    }

    if(mapObject->isDungeonCompleted())
    {
        //Perform Dungeon Cleared message
        //Return to main menu
    }
}

