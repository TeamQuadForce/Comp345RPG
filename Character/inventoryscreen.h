#ifndef INVENTORYSCREEN_H
#define INVENTORYSCREEN_H

#include <QWidget>
#include "weapon.h"
#include "armor.h"
#include "observer.h"
#include "observable.h"
#include "playercharacter.h"

namespace Ui {
    class InventoryScreen;
}

class InventoryScreen : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit InventoryScreen(QWidget *parent = 0);
    ~InventoryScreen();

    void init(PlayerCharacter* aPlayer);
    void update(Observable* aObs);

private:
    Ui::InventoryScreen *ui;

    PlayerCharacter *mPlayer;
    int mIndex;

private slots:
    void equipItem();
    void unequipItem();
    void changeIndex(int aIndex);
};

#endif // INVENTORYSCREEN_H
