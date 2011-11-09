#include "inventoryscreen.h"
#include "ui_inventoryscreen.h"
#include "inventory.h"

InventoryScreen::InventoryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InventoryScreen)
{
    ui->setupUi(this);
    connect(ui->equipUseButton, SIGNAL(clicked()), SLOT(equipItem()));
}

InventoryScreen::~InventoryScreen()
{
    delete ui;
}

void InventoryScreen::init(Inventory *aInventory)
{
    mInventory = aInventory;
}

void InventoryScreen::update(Observable *aObs)
{
    Inventory *inventory = (Inventory*)aObs;
}

void InventoryScreen::equipItem()
{
}

void InventoryScreen::unequipItem()
{

}
