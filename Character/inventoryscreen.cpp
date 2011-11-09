#include "inventoryscreen.h"
#include "ui_inventoryscreen.h"
#include "inventory.h"

class Inventory;

InventoryScreen::InventoryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InventoryScreen)
{
    ui->setupUi(this);
}

InventoryScreen::~InventoryScreen()
{
    delete ui;
}

void InventoryScreen::update(Observable *aObs)
{
    Inventory *inventory = (Inventory*)aObs;
}
