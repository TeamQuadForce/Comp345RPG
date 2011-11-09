#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include "weapon.h"
#include "armor.h"
#include "observer.h"
#include "observable.h"
#include "inventory.h"

namespace Ui {
    class InventoryScreen;
}
class Inventory;

class InventoryScreen : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit InventoryScreen(QWidget *parent = 0);
    ~InventoryScreen();

    void init(Inventory* aInventory);
    void update(Observable* aObs);

private:
    Ui::InventoryScreen *ui;

    Inventory *mInventory;

private slots:
    void equipItem();
    void unequipItem();
};

#endif // INVENTORY_H
