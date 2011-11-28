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
    delete mLogger;
}

void Dungeon::init(PlayerCharacter *aPlayer, Map *aMap, Logger *aLogger, QString file)
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
    mLogger = new Logger;
    mInventoryScreen->init(mPlayer);

    mPlayer->addObserver(mStatWindow);
    mPlayer->addObserver(mInventoryScreen);

    mPlayer->notifyObservers();

    mStatWindow->show();
    mInventoryScreen->show();
    mLogger->show();
    this->show();
    mLogger->addLogEntry("Lolol");
}


//Method it initialize the map
void Dungeon::initializeMap()
{
    QPixmap characterMaleImage(":/images/Knight1M-SW.gif");
    //QPixmap characterFemaleImage(":/images/Knight1F-SW.gif");
    QPixmap wallImage(":/dungeon/images/wall.jpg");
    QPixmap enemyImage(":/dungeon/images/enemy.jpg");
    QPixmap exitImage(":/dungeon/images/exit.jpg");
    QPixmap chestImage(":/dungeon/images/chest.jpg");
    QPixmap terrainImage(":/dungeon/images/terrain.jpg");

    if(mLayout->count() == 0)
    {
        for (int row = 0; row < mMapObject->mapHeight(); row++)
        {
            mMapGrid.append(QList<QLabel*>());
            for (int column = 0; column < mMapObject->mapWidth(); column++)
            {
                mMapGrid[row].append(new QLabel());

                QString gamePiece = mMapObject->mapGridTileSet(row, column).getGamePiece();

                if (gamePiece.compare("You") == 0)
                {
                    /*
                    if(mPlayer->gender().compare("Female") == 0)
                    {
                        mMapGrid[row][column]->setPixmap(characterFemaleImage);
                    }
                    else
                    {
                        mMapGrid[row][column]->setPixmap(characterMaleImage);
                    }
                    */
                    mMapGrid[row][column]->setPixmap(characterMaleImage);
                }

                if (gamePiece.compare("Exit") == 0)
                {
                     mMapGrid[row][column]->setPixmap(exitImage);
                }

                if (gamePiece.compare("Chest") == 0)
                {
                     mMapGrid[row][column]->setPixmap(chestImage);
                }

                if (gamePiece.compare("Monster") == 0)
                {
                     mMapGrid[row][column]->setPixmap(enemyImage);
                }

                if (gamePiece.compare("Wall") == 0)
                {
                     mMapGrid[row][column]->setPixmap(wallImage);
                }

                if (gamePiece.compare("") == 0)
                {
                     mMapGrid[row][column]->setPixmap(terrainImage);
                }

                mMapGrid[row][column]->setScaledContents(true);
                mMapGrid[row][column]->setObjectName(QString::number(row)+"_"+QString::number(column));
                mMapGrid[row][column]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);                

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
    QPixmap terrainImage(":/dungeon/images/terrain.jpg");
    Map *aMap = (Map*)aObs;
    TileSet tile = aMap->lastModifiedTileSet();
    int row = tile.rowPosition();
    int column = tile.columnPosition();

    QPixmap characterMaleImage(QString(":/images/Knight1M-SW.gif"));
    QPixmap characterFemaleImage(QString(":/images/Knight1F-SW.gif"));

    if(tile.getGamePiece().compare("You") == 0)
    {
        if(mPlayer->gender().compare("Female") == 0)
        {
            mMapGrid[row][column]->setPixmap(characterFemaleImage);
        }
        else
        {
            mMapGrid[row][column]->setPixmap(characterMaleImage);
        }
    }
    else
    {
        mMapGrid[row][column]->setPixmap(terrainImage);
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
