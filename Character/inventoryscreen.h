#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include "weapon.h"
#include "armor.h"
#include "observer.h"
#include "observable.h"

namespace Ui {
    class InventoryScreen;
}

class InventoryScreen : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit InventoryScreen(QWidget *parent = 0);
    ~InventoryScreen();

private:
    Ui::InventoryScreen *ui;

    void update(Observable* aObs);
};

#endif // INVENTORY_H
