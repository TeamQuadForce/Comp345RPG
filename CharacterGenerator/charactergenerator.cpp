#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QDateTime>
#include <QLayout>
#include <QDebug>
#include "charactergenerator.h"
#include "ui_charactergenerator.h"
#include "game.h"
#include <QSound>
#include <QFileDialog>

using namespace std;

CharacterGenerator::CharacterGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterGenerator)
{
    ui->setupUi(this);
    mPlayer = 0;
}

CharacterGenerator::~CharacterGenerator()
{
    delete ui;
    ui = 0;
    delete mPlayer;
    mPlayer = 0;
    delete mStatWindow;
    mStatWindow = 0;
}

//Initialization method for all connect logic for signals and slots
void CharacterGenerator::init()
{
    //Determine the random seed for this playthrough
    qsrand(QDateTime::currentMSecsSinceEpoch());

    mStatWindow = new StatWindow;
    mStatWindow->move(725,50);
    connect(ui->raceComboBox, SIGNAL(currentIndexChanged(int)), SLOT(changePicture()));
    connect(ui->classComboBox, SIGNAL(currentIndexChanged(int)), SLOT(changePicture()));
    connect(ui->genderComboBox, SIGNAL(currentIndexChanged(int)), SLOT(changePicture()));
    connect(ui->rollAbilityScoresButton, SIGNAL(clicked()), SLOT(rollAbilityScores()));
    connect(ui->addStrengthButton, SIGNAL(clicked()), SLOT(addToStrength()));
    connect(ui->addDexterityButton, SIGNAL(clicked()), SLOT(addToDexterity()));
    connect(ui->addConstitutionButton, SIGNAL(clicked()), SLOT(addToConstitution()));
    connect(ui->addIntelligenceButton, SIGNAL(clicked()), SLOT(addToIntelligence()));
    connect(ui->addWisdomButton, SIGNAL(clicked()), SLOT(addToWisdom()));
    connect(ui->addCharismaButton, SIGNAL(clicked()), SLOT(addToCharisma()));
    connect(ui->generateCharacterButton, SIGNAL(clicked()), SLOT(generateCharacter()));
    connect(ui->genderComboBox, SIGNAL(currentIndexChanged(int)), SLOT(readyToGenerate()));
    connect(ui->raceComboBox, SIGNAL(currentIndexChanged(int)), SLOT(readyToGenerate()));
    connect(ui->classComboBox, SIGNAL(currentIndexChanged(int)), SLOT(readyToGenerate()));
    connect(ui->returnToMenuButton, SIGNAL(clicked()), SLOT(returnToMenuButtonPress()));
    connect(ui->saveCharacterButton, SIGNAL(clicked()), SLOT(saveCharacter()));
}

void CharacterGenerator::show()
{
    QWidget::show();
    mStatWindow->show();
}

//Changes the player's picture! FOR FUN :D
void CharacterGenerator::changePicture()
{
    if (ui->classComboBox->currentText() == "Fighter" &&
            ui->raceComboBox->currentText() == "Human")
    {
        if (ui->genderComboBox->currentText() == "Male")
        {
            ui->playerPicture->setPixmap(QPixmap(":/images/Knight1M-SW.gif"));
        }
        else if (ui->genderComboBox->currentText() == "Female")
        {
            ui->playerPicture->setPixmap(QPixmap(":/images/Knight1F-SW.gif"));
        }
        else
        {
            ui->playerPicture->clear();
        }
    }
    else
    {
        ui->playerPicture->clear();
    }
}

//Rolls ability scores using the classical 4d6 remove one method.
//This pseudorandomly rolls 4 six-sided dice, and removes the dice
//with the lowest value, adds the remaining and gives one ability score.
//This is done six times to get all six scores.
void CharacterGenerator::rollAbilityScores()
{
    ui->dicerollList->clear();
    const int NUMBER_OF_ABILITY_DICE = 4;
    int diceTotal = 0;
    QList<int> diceList;
    QList<int> abilityDice;

    //Roll 6 times
    for (int i = 0; i < 6; ++i)
    {
        diceList.clear();
        diceTotal = 0;

        //Roll 4d6
        for (int j = 0; j < NUMBER_OF_ABILITY_DICE; ++j)
        {
            int diceRoll = DiceRoller::d6();
            diceList << diceRoll;
        }

        removeLowestValue(diceList);

        //Get the total of the best 3 dice
        foreach (int value, diceList)
        {
            diceTotal += value;
        }

        abilityDice << diceTotal;
    }

    qSort(abilityDice);
    for (int i = abilityDice.size() - 1; i >= 0; --i)
    {
        ui->dicerollList->addItem(QString::number(abilityDice[i]));
    }

    ui->strengthLine->clear();
    ui->addStrengthButton->setEnabled(true);
    ui->dexterityLine->clear();
    ui->addDexterityButton->setEnabled(true);
    ui->constitutionLine->clear();
    ui->addConstitutionButton->setEnabled(true);
    ui->intelligenceLine->clear();
    ui->addIntelligenceButton->setEnabled(true);
    ui->wisdomLine->clear();
    ui->addWisdomButton->setEnabled(true);
    ui->charismaLine->clear();
    ui->addCharismaButton->setEnabled(true);
}

//Removes the lowest number in a given list of integers.
void CharacterGenerator::removeLowestValue(QList<int> &aList)
{
    if (!aList.isEmpty())
    {
        int index = 0;
        int currentNumber = aList.at(0);

        for (int i = 1; i < aList.size(); ++i)
        {
            if (aList.at(i) < currentNumber)
            {
                currentNumber = aList.at(i);
                index = i;
            }
        }

        aList.removeAt(index);
    }
}

//Called when a character is ready to be generated. This is when
//the user has choseen a race, a class, and filled in all
//ability scores. It will enable the generate character button
void CharacterGenerator::readyToGenerate()
{
    if(!ui->strengthLine->text().isEmpty() &&
        !ui->dexterityLine->text().isEmpty() &&
        !ui->constitutionLine->text().isEmpty() &&
        !ui->intelligenceLine->text().isEmpty() &&
        !ui->wisdomLine->text().isEmpty() &&
        !ui->charismaLine->text().isEmpty() &&
        ui->genderComboBox->currentIndex() != 0 &&
        ui->raceComboBox->currentIndex() != 0 &&
        ui->classComboBox->currentIndex() != 0)
    {
        ui->generateCharacterButton->setEnabled(true);
    }
    else if (ui->generateCharacterButton->isEnabled())
    {
        ui->generateCharacterButton->setEnabled(false);
    }
}

//Add's the currently selected ability score from the list to
//the strength text line when pressing the ADD button
void CharacterGenerator::addToStrength()
{
    if (ui->dicerollList->selectedItems().size() == 1)
    {
        QListWidgetItem *item = ui->dicerollList->selectedItems().first();
        if (!item->isHidden())
        {
            QString selectedAttribute = item->text();
            ui->strengthLine->setText(selectedAttribute);
            item->setHidden(true);
            ui->addStrengthButton->setEnabled(false);
            readyToGenerate();
        }
    }
}

//Add's the currently selected ability score from the list to
//the dexterity text line when pressing the ADD button
void CharacterGenerator::addToDexterity()
{
    if (ui->dicerollList->selectedItems().size() == 1)
    {
        QListWidgetItem *item = ui->dicerollList->selectedItems().first();
        if (!item->isHidden())
        {
            QString selectedAttribute = item->text();
            ui->dexterityLine->setText(selectedAttribute);
            item->setHidden(true);
            ui->addDexterityButton->setEnabled(false);
            readyToGenerate();
        }
    }
}

//Add's the currently selected ability score from the list to
//the constitution text line when pressing the ADD button
void CharacterGenerator::addToConstitution()
{
    if (ui->dicerollList->selectedItems().size() == 1)
    {
        QListWidgetItem *item = ui->dicerollList->selectedItems().first();
        if (!item->isHidden())
        {
            QString selectedAttribute = item->text();
            ui->constitutionLine->setText(selectedAttribute);
            item->setHidden(true);
            ui->addConstitutionButton->setEnabled(false);
            readyToGenerate();
        }
    }
}

//Add's the currently selected ability score from the list to
//the intelligence text line when pressing the ADD button
void CharacterGenerator::addToIntelligence()
{
    if (ui->dicerollList->selectedItems().size() == 1)
    {
        QListWidgetItem *item = ui->dicerollList->selectedItems().first();
        if (!item->isHidden())
        {
            QString selectedAttribute = item->text();
            ui->intelligenceLine->setText(selectedAttribute);
            item->setHidden(true);
            ui->addIntelligenceButton->setEnabled(false);
            readyToGenerate();
        }
    }
}

//Add's the currently selected ability score from the list to
//the wisdom text line when pressing the ADD button
void CharacterGenerator::addToWisdom()
{
    if (ui->dicerollList->selectedItems().size() == 1)
    {
        QListWidgetItem *item = ui->dicerollList->selectedItems().first();
        if (!item->isHidden())
        {
            QString selectedAttribute = item->text();
            ui->wisdomLine->setText(selectedAttribute);
            item->setHidden(true);
            ui->addWisdomButton->setEnabled(false);
            readyToGenerate();
        }
    }
}

//Add's the currently selected ability score from the list to
//the charisma text line when pressing the ADD button
void CharacterGenerator::addToCharisma()
{
    if (ui->dicerollList->selectedItems().size() == 1)
    {
        QListWidgetItem *item = ui->dicerollList->selectedItems().first();
        if (!item->isHidden())
        {
            QString selectedAttribute = item->text();
            ui->charismaLine->setText(selectedAttribute);
            item->setHidden(true);
            ui->addCharismaButton->setEnabled(false);
            readyToGenerate();
        }
    }
}

//Generates a new character based on the user's specified race, class, and
//ability scores.
void CharacterGenerator::generateCharacter()
{
    if (mPlayer != 0)
    {
        delete mPlayer;
        mPlayer = 0;
    }

    mPlayer = new PlayerCharacter(ui->characterName->text(),
                                  ui->genderComboBox->currentText(),
                                  ui->raceComboBox->currentText(),
                                  ui->classComboBox->currentText(),
                                  ui->playerPicture->pixmap()->pixmapData());

    mPlayer->modifyAbilityScores(ui->strengthLine->text().toShort(),
                                 ui->dexterityLine->text().toShort(),
                                 ui->constitutionLine->text().toShort(),
                                 ui->intelligenceLine->text().toShort(),
                                 ui->wisdomLine->text().toShort(),
                                 ui->charismaLine->text().toShort());

    mPlayer->addObserver(mStatWindow);

    mPlayer->init();

    ui->returnToMenuButton->setEnabled(true);
    ui->saveCharacterButton->setEnabled(true);
}

//Levels up the player, this will level up the class increasing
//both hitpoints and attack bonuses
void CharacterGenerator::returnToMenuButtonPress()
{
    reset();
    if (mPlayer != 0)
    {
        delete mPlayer;
        mPlayer = 0;
    }

    Game *game = (Game*)this->parentWidget();
    game->setCurrentIndex(0);
    mStatWindow->hide();
}

void CharacterGenerator::saveCharacter()
{
    QString fileName = QFileDialog::getSaveFileName();
   // QString fileName = QString("%1.baus").arg(mPlayer->name());
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<mPlayer->race()<<endl;
    out<<mPlayer->className()<<endl;
    out<<mPlayer->gender()<<endl;
    out<<mPlayer->name()<<endl;
    out<<mPlayer->abilityScore(PlayerCharacter::Strength)<<endl;
    out<<mPlayer->abilityScore(PlayerCharacter::Dexterity)<<endl;
    out<<mPlayer->abilityScore(PlayerCharacter::Constitution)<<endl;
    out<<mPlayer->abilityScore(PlayerCharacter::Intelligence)<<endl;
    out <<mPlayer->abilityScore(PlayerCharacter::Wisdom)<<endl;
    out<<mPlayer->abilityScore(PlayerCharacter::Charisma)<<endl;
    file.close();




}
//Resets the GUI back to it's default state
void CharacterGenerator::reset()
{
    mStatWindow->reset();
    ui->characterName->clear();
    ui->classComboBox->setCurrentIndex(0);
    ui->raceComboBox->setCurrentIndex(0);
    ui->genderComboBox->setCurrentIndex(0);
    ui->playerPicture->clear();
    ui->dicerollList->clear();
    ui->strengthLine->clear();
    ui->addStrengthButton->setEnabled(true);
    ui->dexterityLine->clear();
    ui->addDexterityButton->setEnabled(true);
    ui->constitutionLine->clear();
    ui->addConstitutionButton->setEnabled(true);
    ui->intelligenceLine->clear();
    ui->addIntelligenceButton->setEnabled(true);
    ui->wisdomLine->clear();
    ui->addWisdomButton->setEnabled(true);
    ui->charismaLine->clear();
    ui->addCharismaButton->setEnabled(true);
    ui->generateCharacterButton->setEnabled(false);
    ui->saveCharacterButton->setEnabled(false);
}
