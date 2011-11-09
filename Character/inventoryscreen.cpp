#include "inventoryscreen.h"
#include "ui_inventoryscreen.h"
#include "inventory.h"
#include <QDebug>

InventoryScreen::InventoryScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InventoryScreen)
{
    ui->setupUi(this);
    connect(ui->equipUseButton, SIGNAL(clicked()), SLOT(equipItem()));
    connect(ui->unequipButton, SIGNAL(clicked()), SLOT(unequipItem()));
    connect(ui->inventoryPane, SIGNAL(currentRowChanged(int)), SLOT(changeIndex(int)));
}

InventoryScreen::~InventoryScreen()
{
    delete ui;
}

void InventoryScreen::init(PlayerCharacter *aPlayer)
{
    mPlayer = aPlayer;
}

void InventoryScreen::update(Observable *aObs)
{
    PlayerCharacter *player = (PlayerCharacter*)aObs;

    ui->inventoryPane->clear();

    foreach(Item *item, player->inventory()->backpack())
    {
        if (item->itemType() == Item::Weapon)
        {
            if (item->isEquipped())
            {
                ui->inventoryPane->addItem(QString("%1 (E)").arg(((Weapon*)item)->itemDescription()));
            }
            else
            {
                ui->inventoryPane->addItem(((Weapon*)item)->itemDescription());
            }
        }
        else if (item->itemType() == Item::Armor)
        {
            if (item->isEquipped())
            {
                ui->inventoryPane->addItem(QString("%1 (E)").arg(((Armor*)item)->itemDescription()));
                Armor::ArmorType armorType = ((Armor*)item)->armorType();

                if (armorType == Armor::BodyArmor)
                {
                    ui->bodyArmorLabel->setText(((Armor*)item)->itemName());
                }
            }
            else
            {
                ui->inventoryPane->addItem(((Armor*)item)->itemDescription());
            }
        }
    }
}

void InventoryScreen::equipItem()
{
    mPlayer->inventory()->equipItem(mIndex);
    mPlayer->notifyObservers();
}

void InventoryScreen::unequipItem()
{
    mPlayer->inventory()->unequipItem(mIndex);
    mPlayer->notifyObservers();
}

void InventoryScreen::changeIndex(int aIndex)
{
    if (aIndex < 0)
    {
        mIndex = 0;
    }
    else
    {
        mIndex = aIndex;
    }
}
