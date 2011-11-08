#include "statwindow.h"
#include "ui_statwindow.h"
#include <QPixmap>

StatWindow::StatWindow(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowTitleHint),
    ui(new Ui::StatWindow)
{
    ui->setupUi(this);
}

StatWindow::~StatWindow()
{
    delete ui;
}

//Update with stats from the player which are useful to the user which includes:
//Ability scores, Ability modifiers
//Hit points, Armor class
//Attack bonus
void StatWindow::update(PlayerCharacter *aPlayer)
{
    //Change name, race, gender, class
    ui->name->setText(aPlayer->name());
    ui->race->setText(aPlayer->race());
    ui->gender->setText(aPlayer->gender());
    ui->playerClass->setText(aPlayer->className());

    //Change the ability scores
    ui->playerStr->setText(QString::number(aPlayer->abilityScore(PlayerCharacter::Strength)));
    ui->playerDex->setText(QString::number(aPlayer->abilityScore(PlayerCharacter::Dexterity)));
    ui->playerCon->setText(QString::number(aPlayer->abilityScore(PlayerCharacter::Constitution)));
    ui->playerInt->setText(QString::number(aPlayer->abilityScore(PlayerCharacter::Intelligence)));
    ui->playerWis->setText(QString::number(aPlayer->abilityScore(PlayerCharacter::Wisdom)));
    ui->playerCha->setText(QString::number(aPlayer->abilityScore(PlayerCharacter::Charisma)));

    //Change the picture
    ui->playerPortrait->clear();
    ui->playerPortrait->setPixmap(QPixmap(aPlayer->portrait().pixmapData()));

    //Change the ability modifiers, make sure there is a + if the ability score is positive
    short abilityMod = aPlayer->abilityModifier(PlayerCharacter::Strength);
    if (abilityMod > 0)
    {
        ui->playerStrMod->setText(QString("+%1").arg(abilityMod));
    }
    else
    {
        ui->playerStrMod->setText(QString::number(abilityMod));
    }

    abilityMod = aPlayer->abilityModifier(PlayerCharacter::Dexterity);
    if (abilityMod > 0)
    {
        ui->playerDexMod->setText(QString("+%1").arg(abilityMod));
    }
    else
    {
        ui->playerDexMod->setText(QString::number(abilityMod));
    }

    abilityMod = aPlayer->abilityModifier(PlayerCharacter::Constitution);
    if (abilityMod > 0)
    {
        ui->playerConMod->setText(QString("+%1").arg(abilityMod));
    }
    else
    {
        ui->playerConMod->setText(QString::number(abilityMod));
    }

    abilityMod = aPlayer->abilityModifier(PlayerCharacter::Intelligence);
    if (abilityMod > 0)
    {
        ui->playerIntMod->setText(QString("+%1").arg(abilityMod));
    }
    else
    {
        ui->playerIntMod->setText(QString::number(abilityMod));
    }

    abilityMod = aPlayer->abilityModifier(PlayerCharacter::Wisdom);
    if (abilityMod > 0)
    {
        ui->playerWisMod->setText(QString("+%1").arg(abilityMod));
    }
    else
    {
        ui->playerWisMod->setText(QString::number(abilityMod));
    }

    abilityMod = aPlayer->abilityModifier(PlayerCharacter::Charisma);
    if (abilityMod > 0)
    {
        ui->playerChaMod->setText(QString("+%1").arg(abilityMod));
    }
    else
    {
        ui->playerChaMod->setText(QString::number(abilityMod));
    }
    //End of ability modifiers

    //Level
    ui->level->setText((QString::number(aPlayer->level())));

    //Hit points
    ui->hitPoints->setText(QString::number(aPlayer->hitPoints()));

    //AC
    ui->armorClass->setText(QString::number(aPlayer->armorClass()));

    //Change the melee and ranged bonuses, make sure there's a plus on positive values
    QString meleeBonuses;
    QString rangedBonuses;

    for (int i = 1; i <= aPlayer->characterClass()->numberOfAttacks(); ++i)
    {
        short bonus;
        if (i != aPlayer->characterClass()->numberOfAttacks())
        {
            bonus = aPlayer->meleeAttackBonus(i);
            if (bonus >= 0)
            {
                meleeBonuses.append(QString("+%1 / ").arg(bonus));
            }
            else
            {
                meleeBonuses.append(QString("%1 / ").arg(bonus));
            }

            bonus = aPlayer->rangedAttackBonus(i);
            if (bonus >= 0)
            {
                rangedBonuses.append(QString("+%1 / ").arg(bonus));

            }
            else
            {
                rangedBonuses.append(QString("%1 / ").arg(bonus));
            }
        }
        else
        {
            bonus = aPlayer->meleeAttackBonus(i);
            if (bonus >= 0)
            {
                meleeBonuses.append(QString("+%1").arg(bonus));

            }
            else
            {
                meleeBonuses.append(QString("%1").arg(bonus));
            }

            bonus = aPlayer->rangedAttackBonus(i);
            if (bonus >= 0)
            {
                rangedBonuses.append(QString("+%1").arg(bonus));
            }
            else
            {
                rangedBonuses.append(QString("%1").arg(bonus));
            }
        }
    }

    ui->meleeBonus->setText(meleeBonuses);
    ui->rangedBonus->setText(rangedBonuses);
    //End of melee and ranged bonuses
}

void StatWindow::reset()
{
    ui->name->setText("N/A");
    ui->gender->setText("N/A");
    ui->race->setText("N/A");
    ui->playerClass->setText("N/A");
    ui->playerStr->setText("N/A");
    ui->playerDex->setText("N/A");
    ui->playerCon->setText("N/A");
    ui->playerInt->setText("N/A");
    ui->playerWis->setText("N/A");
    ui->playerCha->setText("N/A");
    ui->playerStrMod->setText("");
    ui->playerDexMod->setText("");
    ui->playerConMod->setText("");
    ui->playerIntMod->setText("");
    ui->playerWisMod->setText("");
    ui->playerChaMod->setText("");
    ui->playerPortrait->clear();
    ui->level->setText("N/A");
    ui->hitPoints->setText("N/A");
    ui->armorClass->setText("10");
    ui->meleeBonus->setText("N/A");
    ui->rangedBonus->setText("N/A");
}
