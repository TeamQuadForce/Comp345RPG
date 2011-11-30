#include "dungeon.h"
#include "ui_dungeon.h"
#include <QFileDialog>
#include <QTextStream>
#include "game.h"
#include "randomchestbuilder.h"
#include "leveledchestbuilder.h"
#include <QDebug>
#include <QMessageBox>
#include "inventory.h"
#include "armor.h"
#include "weapon.h"

const int mNumOfAllowedMoves = 6;

Dungeon::Dungeon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dungeon)
{
    ui->setupUi(this);
}
//Dungeon Destructor
Dungeon::~Dungeon()
{
    delete ui;
    ui = 0;
    delete mStatWindow;
    mStatWindow = 0;
    delete mInventoryScreen;
    mInventoryScreen = 0;
    delete mLogger;
    mLogger = 0;
}
//Initialize dungeon : associate player, map, logger , stats window and inventory to the dungeon.
void Dungeon::init(PlayerCharacter *aPlayer, Map *aMap, QString file, bool aMapIsArena)
{
    mCanExit = false;

    mLayout = new QGridLayout();
    mLayout->setSpacing(0);
    mLayout->setVerticalSpacing(0);

    filename = file;

    assignMovementOperations();
    mMapObject = aMap;
    mMapObject->addObserver(this);

    mPlayer = aPlayer;
    initializeMap();

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

    ui->attackDirectionFrame->hide();
    ui->moveDirectionFrame->hide();
    mMoveCounter = mNumOfAllowedMoves;

    mIsArena = aMapIsArena;

    playerList.append(mPlayer);
    playerList.append(MonsterRepertoire::getUniqueInstance()->getMonster(mPlayer->level()));
    generateTurnOrder();
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
    int numberOfMonsters = 0;

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
                     numberOfMonsters = numberOfMonsters + 1;
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
    connect(ui->moveOptionButton, SIGNAL(clicked()), SLOT(startMoveOption()));
    connect(ui->attackOptionButton, SIGNAL(clicked()), SLOT(startAttackOption()));
    connect(ui->endTurnOptionButton, SIGNAL(clicked()), SLOT(endTurn()));

    connect(ui->movementButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(moveCharacter(QAbstractButton*)));
    connect(ui->attackButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(characterAttack(QAbstractButton*)));
}

//Method to determine the monsters and the turn order the players on the map
void Dungeon::generateTurnOrder()
{
    QList <int> characterInitiativeVector;
    foreach(Player* player, playerList)
    {
        characterInitiativeVector.append(player->rollInitiative(mLogger));
    }

    //Determine the order of the players on the map
    playerTurnOrderList = turnOrderSort(playerList, characterInitiativeVector);
}

//Method to determine the turn order of player and monsters (determined by initiative)
QList<Player*> Dungeon::turnOrderSort(QList<Player*> characterVector, QList<int> characterInitiativeVector)
{
    if (!mCanExit)
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
                        Player* characterTemp = characterVector[index];
                        int initiativeTemp = characterInitiativeVector[index];
                        characterVector[index] = characterVector[counter + 1];
                        characterInitiativeVector[index] = characterInitiativeVector[counter + 1];
                        characterVector[counter + 1] = characterTemp;
                        characterInitiativeVector[counter + 1] = initiativeTemp;
                    }
                }
            }
       }
       //Return the sorted vector
       return characterVector;
    }

    return characterVector;
}

//Slot to move the character
void Dungeon::moveCharacter(QAbstractButton* button)
{
    bool isChest = false;

    if(mMoveCounter > 0)
    {
        mMapObject->moveCharacter(button->text(), isChest);

        if (isChest)
        {
            mLogger->addLogEntry("Character Steps on Chest");

            if (mIsArena)
            {
                setChestBuilder(new LeveledChestBuilder);
            }
            else
            {
                setChestBuilder(new RandomChestBuilder);
            }

            constructChest();
            mChestBuilder->addItems();

            foreach(Item* item, chest()->itemList())
            {
                mLogger->addLogEntry(item->itemDescription()+" has been added to player inventory.");
                mPlayer->inventory()->addItem(item);
                mPlayer->notifyObservers();
            }
        }

        mMoveCounter = mMoveCounter - 1;

        if(mMoveCounter < 1)
        {
            ui->moveDirectionFrame->hide();
            mMoveCounter = mNumOfAllowedMoves;
        }
    }
}

//Slot for character to attack
void Dungeon::characterAttack(QAbstractButton *button)
{
    QString directionOfAttack = button->text();

    //Check the radio button and make sure the character has a weapon of that type equipped
    if (ui->meleeButton->isChecked())
    {
        bool hasEquipped = false;
        foreach (Item* item, mPlayer->inventory()->backpack())
        {
            if (item->itemType() == Item::Weapon)
            {
                Weapon* weapon = (Weapon*) item;
                if (weapon->weaponType() == Weapon::Melee && weapon->isEquipped())
                {
                    hasEquipped = true;
                }
            }
        }

        if (!hasEquipped)
        {
            mLogger->addLogEntry("Player does not have a melee weapon equipped, can't attack.");
            return;
        }
    }
    else if (ui->rangedButton->isChecked())
    {
        bool hasEquipped = false;
        foreach (Item* item, mPlayer->inventory()->backpack())
        {
            if (item->itemType() == Item::Weapon)
            {
                Weapon* weapon = (Weapon*) item;
                if (weapon->weaponType() == Weapon::Ranged && weapon->isEquipped())
                {
                    hasEquipped = true;
                }
            }
        }

        if (!hasEquipped)
        {
            mLogger->addLogEntry("Player does not have a ranged weapon equipped, can't attack.");
            return;
        }
    }

    bool monsterIsThere = mMapObject->isAMonsterThere(directionOfAttack);

    //attack logic from player -> monster
    if (monsterIsThere)
    {
        //roll to see if you hit. d20 + str modifier + base attack bonus, must be equal to or
        //higher than the enemy's AC
        short hitNumber = mPlayer->rollHit(mLogger);
        Monster* monster = (Monster*) playerList[1];
        mLogger->addLogEntry(QString("You attempt to hit with %1 against enemy AC of %2").arg(hitNumber).arg(monster->armorClass()));
        if (hitNumber >= monster->armorClass())
        {
            mLogger->addLogEntry(QString(""));
            short damage = mPlayer->attack(mLogger);
            mLogger->addLogEntry(QString("Monster takes %1 damage! And has %2 HP remaining.").arg(damage).arg(monster->hitPoints()));
            bool isDead = monster->takeDamage(damage);
            if (isDead)
            {
                mLogger->addLogEntry(QString("You dumpstered the %1.").arg(monster->name()));
                //playerList.removeOne(monster);
               // mMapObject->killMonsters();
                mCanExit = true;
            }
        }
        else
        {
            mLogger->addLogEntry("You missed!");
        }

        ui->attackDirectionFrame->hide();
    }
}

//Perform start of move procedure
void Dungeon::startMoveOption()
{
    ui->moveOptionButton->setEnabled(false);
    ui->attackDirectionFrame->hide();
    ui->moveDirectionFrame->show();
}

//Perform start of attack procedure (backend)
void Dungeon::startAttackOption()
{
    ui->attackOptionButton->setEnabled(false);
    ui->attackDirectionFrame->show();
    ui->moveDirectionFrame->hide();
}

//End the user's turn
void Dungeon::endTurn()
{
    setTurnActionButtons(true);
    ui->optionsFrame->show();
    ui->attackDirectionFrame->hide();
    ui->moveDirectionFrame->hide();
    mMoveCounter = mNumOfAllowedMoves;
    startNextPlayerTurn();
}

void Dungeon::startNextPlayerTurn()
{
    mMoveCounter = mNumOfAllowedMoves;

    if (!playerTurnOrderList.isEmpty())
    {
        Player* player = playerTurnOrderList.takeFirst();
        if (player->type() == "Monster")
        {
            //CHANGE
            monsterTurn(playerList.at(1));
        }
    }
    else
    {
        generateTurnOrder();
        startNextPlayerTurn();
    }
}

void Dungeon::monsterTurn(Player* aPlayer)
{
    bool hasAttacked = false;
    mMapObject->moveMonster(0, hasAttacked);
    if (hasAttacked)
    {
        //roll to see if you hit. d20 + str modifier + base attack bonus, must be equal to or
        //higher than the players AC
        short hitNumber = aPlayer->rollHit(mLogger);
        mLogger->addLogEntry(QString("Enemy attempts to hit with %1 against player AC of %2").arg(hitNumber).arg(mPlayer->armorClass()));
        if (hitNumber >= mPlayer->armorClass())
        {
            mLogger->addLogEntry(QString(""));
            short damage = aPlayer->attack(mLogger);
            mLogger->addLogEntry(QString("Player takes %1 damage!").arg(damage));
            bool isDead = mPlayer->takeDamage(damage);
            if (isDead)
            {
                mLogger->addLogEntry("You have died. Restart the game.");
                QMessageBox deadBox;
                deadBox.setDetailedText("You died.");
                deadBox.setModal(true);
                deadBox.exec();
                qApp->quit();
            }
        }
        else
        {
            mLogger->addLogEntry("Enemy missed!");
        }
    }

    startNextPlayerTurn();
}

//Method to set the main turn actions all on or off
void Dungeon::setTurnActionButtons(bool enable)
{
    ui->moveOptionButton->setEnabled(enable);
    ui->attackOptionButton->setEnabled(enable);
    ui->endTurnOptionButton->setEnabled(enable);
}

//Update Observer
void Dungeon::update(Observable *aObs)
{
    QPixmap terrainImage(":/dungeon/images/terrain.jpg");
    QPixmap monsterImage(":dungeon/images/enemy.jpg");
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
    else if (tile.getGamePiece().compare("Monster") == 0)
    {
        mMapGrid[row][column]->setPixmap(monsterImage);
    }
    else
    {
        mMapGrid[row][column]->setPixmap(terrainImage);
    }

    //Level Up player and save player inside a new file
    if(mMapObject->isDungeonCompleted() && mCanExit)
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

//Associate an instance of chestBuilder to the dungeon
void Dungeon::setChestBuilder(ChestBuilder *aChestBuilder)
{
    if (mChestBuilder != 0)
    {
        delete mChestBuilder;
        mChestBuilder = 0;
    }

    mChestBuilder = aChestBuilder;
}

//Retrieve an instance of a chest from the chest builder
Chest * Dungeon::chest()
{
    if (mChestBuilder != 0 && mChestBuilder->getChest() != 0)
    {
        return mChestBuilder->getChest();
    }

    return 0;
}

//Constructs a chest based on the player level
void Dungeon::constructChest()
{
    mChestBuilder->createNewChest(mPlayer->level());
}
