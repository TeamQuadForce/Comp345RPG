#ifndef DUNGEON_H
#define DUNGEON_H

#include <QWidget>
#include <QList>
#include <QAbstractButton>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "map.h"
#include "player.h"
#include "playercharacter.h"
#include "statwindow.h"
#include "inventoryscreen.h"
#include "chest.h"
#include "chestbuilder.h"
#include "diceroller.h"
#include "logger.h"

namespace Ui {
    class Dungeon;
}

class Dungeon : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit Dungeon(QWidget *parent = 0);
    Dungeon();
    ~Dungeon();

    void init(PlayerCharacter *aPlayer, Map *aMap, QString filename, bool aMapIsArena);
    void assignMovementOperations();
    void update(Observable *aObs);

    QString mapStyleSheet(TileSet aTile);

private:
    Ui::Dungeon *ui;
    void initializeMap();
    void generateTurnOrder(int numberOfMonsters);
    QVector<PlayerCharacter*> turnOrderSort(QVector<PlayerCharacter*> characterVector, QVector<int> characterInitiativeVector);


    Map *mMapObject;
    QGridLayout *mLayout;
    QList<QList<QLabel*> > mMapGrid;
    QList <PlayerCharacter*> playerTurnOrderList;
    QString filename;
    bool mIsArena;

    PlayerCharacter *mPlayer;
    StatWindow *mStatWindow;
    InventoryScreen *mInventoryScreen;
    Logger *mLogger;

    //Director specific functions for chests
    ChestBuilder* mChestBuilder;
    void setChestBuilder(ChestBuilder* aChestBuilder);
    Chest* chest();
    void constructChest();

private slots:
    void moveCharacter(QAbstractButton *button);
};

#endif // DUNGEON_H
