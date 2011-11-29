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
    ui = 0;
    delete mStatWindow;
    mStatWindow = 0;
    delete mInventoryScreen;
    mInventoryScreen = 0;
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

    mPlayer = aPlayer;
    initializeMap();
    testDetermineTurnOrder(); //test determine turn order

    mStatWindow = new StatWindow;
    mInventoryScreen = new InventoryScreen;
    mLogger = new Logger;
    mInventoryScreen->init(mPlayer);
    mLogger->addLogEntry("Character Stats Window Initialized");

    mPlayer->addObserver(mStatWindow);
    mLogger->addLogEntry("Stat Window Observer has been added to player");
    mPlayer->addObserver(mInventoryScreen);
    mLogger->addLogEntry("Character Inventory Screen Initialized");

    mPlayer->notifyObservers();
    mLogger->addLogEntry("Observer Notified");

    mStatWindow->show();
    mLogger->addLogEntry("Stats Window Displayed");
    mInventoryScreen->show();
    mLogger->addLogEntry("Inventory Window Displayed");
    mLogger->show();
    this->show();

}

//Method it initialize the map
void Dungeon::initializeMap()
{
    QPixmap characterMaleImage(":/images/Knight1M-SW.gif");
    QPixmap characterFemaleImage(":/images/Knight1F-SW.gif");
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
                    if(mPlayer->gender().compare("Female") == 0)
                    {
                        mMapGrid[row][column]->setPixmap(characterFemaleImage);
                    }
                    else
                    {
                        mMapGrid[row][column]->setPixmap(characterMaleImage);
                    }
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

//Method to test determineTrunOrder
void Dungeon::testDetermineTurnOrder()
{
    int numOfMonsters = 4;
    QVector <PlayerCharacter*> characterVector;
    QVector <int> characterInitiativeVector;

    QString testName[4] = {"Sam", "Joe", "Carl", "Bob"};
    QString testGender[4] = {"Female", "Male", "Male", "Male"};
    QString testRace[4] = {"Human", "Human", "Human", "Human"};
    QString testClassName[4] = {"Fighter", "Fighter", "Fighter", "Fighter"};
    int testDexterity[4] = {4, 3, 2, 1};

    characterVector.append(mPlayer);
    characterInitiativeVector.append(DiceRoller::d20() + mPlayer->abilityScore(PlayerCharacter::Dexterity));

    for(int counter = 0; counter < numOfMonsters; counter++)
    {
        characterVector.append(new PlayerCharacter(testName[counter],testGender[counter],testRace[counter],testClassName[counter]));
        characterVector.last()->modifyAbilityScores(1,testDexterity[counter],1,1,1,1);
        characterVector.last()->init();
        characterInitiativeVector.append(DiceRoller::d20() + characterVector.last()->abilityScore(PlayerCharacter::Dexterity));
    }

    characterVector = determineTurnOrder(characterVector, characterInitiativeVector);
}

//Method to determine the turn order of player and monsters
QVector <PlayerCharacter*> Dungeon::determineTurnOrder(QVector <PlayerCharacter*> characterVector,
                                                       QVector <int> characterInitiativeVector)
{
   //Sort in decreasing initiative order
   for (int index = 0; index < characterVector.size(); index++)
   {
        for(int counter = index; counter < characterVector.size() - 1; counter++)
        {
            if(characterInitiativeVector[counter + 1] >= characterInitiativeVector[index])
            {
                if(characterInitiativeVector[counter + 1] != characterInitiativeVector[index])
                {
                    PlayerCharacter* characterTemp = characterVector[index];
                    int initiativeTemp = characterInitiativeVector[index];
                    characterVector[index] = characterVector[counter + 1];
                    characterInitiativeVector[index] = characterInitiativeVector[counter + 1];
                    characterVector[counter + 1] = characterTemp;
                    characterInitiativeVector[counter + 1] = initiativeTemp;
                }
            }
        }
   }

   return characterVector;
}

//Slot to move the character
void Dungeon::moveCharacter(QAbstractButton* button)
{
    bool isChest = false;
    mMapObject->moveCharacter(button->text(), isChest);

    if (isChest)
    {

    }
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
        mLogger->addLogEntry("Dungeon Completed!");
        mStatWindow->hide();
        mInventoryScreen->hide();
        mLogger->hide();
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

void Dungeon::setChestBuilder(ChestBuilder *aChestBuilder)
{
    if (mChestBuilder != 0)
    {
        delete mChestBuilder;
        mChestBuilder = 0;
    }

    mChestBuilder = aChestBuilder;
}

Chest * Dungeon::chest()
{
    if (mChestBuilder != 0 && mChestBuilder->getChest() != 0)
    {
        return mChestBuilder->getChest();
    }

    return 0;
}

void Dungeon::constructChest()
{
    mChestBuilder->createNewChest();
}
