#ifndef DUNGEON_H
#define DUNGEON_H

#include <QWidget>
#include <Qlist>
#include <QAbstractButton>
#include <QGridLayout>
#include <QPushButton>

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
    Map *mapObject;
    QGridLayout *layout;
    QList<QList<QPushButton*> > mapGrid;

    PlayerCharacter *mPlayer;
    StatWindow *mStatWindow;
    InventoryScreen *mInventoryScreen;

private slots:
    void moveCharacter(QAbstractButton *button);
};

#endif // DUNGEON_H
