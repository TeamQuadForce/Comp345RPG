#include "dungeon.h"
#include "ui_dungeon.h"
#include <QFileDialog>
#include <QTextStream>
#include "game.h"

Dungeon::Dungeon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dungeon)
{
    ui->setupUi(this);
}

Dungeon::~Dungeon()
{
    delete ui;
    delete mStatWindow;
    delete mInventoryScreen;
}

void Dungeon::init(PlayerCharacter *aPlayer, Map *aMap, QString file)
{
    mLayout = new QGridLayout();
    mLayout->setSpacing(0);
    mLayout->setVerticalSpacing(0);

    filename=file;

    assignMovementOperations();
    mMapObject = aMap;
    mMapObject->addObserver(this);
    initializeMap();

    mPlayer = aPlayer;

    mStatWindow = new StatWindow;
    mInventoryScreen = new InventoryScreen;
    mInventoryScreen->init(mPlayer);

    mPlayer->addObserver(mStatWindow);
    mPlayer->addObserver(mInventoryScreen);

    mPlayer->notifyObservers();

    mStatWindow->show();
    mInventoryScreen->show();
    this->show();
}


//Method it initialize the map
void Dungeon::initializeMap()
{
    if(mLayout->count() == 0)
    {
        for (int row = 0; row < mMapObject->mapHeight(); row++)
        {
            mMapGrid.append(QList<QPushButton*>() );
            for (int column = 0; column < mMapObject->mapWidth(); column++)
            {
                mMapGrid[row].append(new QPushButton(mMapObject->mapGridTileSet(row, column).getGamePiece()));
                mMapGrid[row][column]->setObjectName(QString::number(row)+"_"+QString::number(column));
                mMapGrid[row][column]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                mMapGrid[row][column]->setStyleSheet(mapStyleSheet(mMapObject->mapGridTileSet(row, column)));

                mLayout->addWidget(mMapGrid[row][column], row, column);
            }
        }

        ui->mapDungeonFrame->setLayout(mLayout);
    }
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

    mMapObject->moveCharacter(button->text());
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



    if(tile.getGamePiece().compare("You") == 0)
    {
        mMapGrid[row][column]->setText("You");
        mMapGrid[row][column]->setStyleSheet("background-color: blue;");
    }
    else
    {
        mMapGrid[row][column]->setText("");
        mMapGrid[row][column]->setStyleSheet("background-color: white;");
    }

    if(mMapObject->isDungeonCompleted())
    {
        mStatWindow->hide();
        mInventoryScreen->hide();
        mPlayer->levelUp();

        QString fileName = filename;
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out<<mPlayer->race()<<endl;
        out<<mPlayer->className()<<endl;
        out<<mPlayer->gender()<<endl;
        out<<mPlayer->name()<<endl;
        out<<mPlayer->level()<<endl;
        out<<mPlayer->abilityScore(PlayerCharacter::Strength)<<endl;
        out<<mPlayer->abilityScore(PlayerCharacter::Dexterity)<<endl;
        out<<mPlayer->abilityScore(PlayerCharacter::Constitution)<<endl;
        out<<mPlayer->abilityScore(PlayerCharacter::Intelligence)<<endl;
        out<<mPlayer->abilityScore(PlayerCharacter::Wisdom)<<endl;
        out<<mPlayer->abilityScore(PlayerCharacter::Charisma)<<endl;
        out<<fileName<<endl;
        file.close();

//        Game *game = (Game*)this->parentWidget();
//        game->removeWidget(this);
//        game->setCurrentIndex(0);
        qApp->quit();
    }
}

QString Dungeon::mapStyleSheet(TileSet aTile)
{
    QString styleSheet = "";
    if(aTile.getGamePiece() == "Wall")
    {
        styleSheet = QString("background-color: grey;");
    }
    else if(aTile.getGamePiece() == "Chest")
    {
        styleSheet = QString("background-color: yellow;");
    }
    else if(aTile.getGamePiece() == "Monster")
    {
        styleSheet = QString("background-color: red;");
    }
    else if(aTile.getGamePiece() == "Exit")
    {
        styleSheet = QString("background-color: black;");
    }
    else if(aTile.getGamePiece() == "You")
    {
        styleSheet = QString("background-color: blue;");
    }
    else if(aTile.getGamePiece() == "")
    {
        styleSheet = QString("background-color: white;");
    }
    return styleSheet;
}
