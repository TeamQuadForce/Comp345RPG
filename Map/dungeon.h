#ifndef DUNGEON_H
#define DUNGEON_H

#include <QWidget>
#include <QList>
#include <QAbstractButton>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "map.h"
#include "playercharacter.h"
#include "statwindow.h"
#include "inventoryscreen.h"

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

    void init(PlayerCharacter *aPlayer, Map *aMap);
    void assignMovementOperations();
    void update(Observable *aObs);

    QString mapStyleSheet(TileSet aTile);

private:
    Ui::Dungeon *ui;
    void initializeMap();
    Map *mMapObject;
    QGridLayout *mLayout;
    QList<QList<QLabel*> > mMapGrid;
    //QList<QList<QPushButton*> > mMapGrid;

    PlayerCharacter *mPlayer;
    StatWindow *mStatWindow;
    InventoryScreen *mInventoryScreen;

private slots:
    void moveCharacter(QAbstractButton *button);
};

#endif // DUNGEON_H
