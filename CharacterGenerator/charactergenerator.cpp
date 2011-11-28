#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QDateTime>
#include <QLayout>
#include <QDebug>
#include <QSound>
#include <QFileDialog>

#include "game.h"
#include "brutebuilder.h"
#include "nimblebuilder.h"
#include "tankbuilder.h"
#include "charactergenerator.h"
#include "ui_charactergenerator.h"

using namespace std;

CharacterGenerator::CharacterGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterGenerator)
{
    ui->setupUi(this);
    mCharacterBuilder = 0;
}

CharacterGenerator::~CharacterGenerator()
{
    delete ui;
    ui = 0;
    delete mStatWindow;
    mStatWindow = 0;
    delete mCharacterBuilder;
    mCharacterBuilder = 0;
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
    connect(ui->typeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(readyToGenerate()));
    connect(ui->rollAbilityScoresButton, SIGNAL(clicked()), SLOT(rollAbilityScores()));
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

    ui->typeComboBox->setEnabled(true);
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
    if(ui->genderComboBox->currentIndex() != 0 &&
            ui->raceComboBox->currentIndex() != 0 &&
            ui->classComboBox->currentIndex() != 0 &&
            ui->typeComboBox->currentIndex() != 0)
    {
        ui->generateCharacterButton->setEnabled(true);
    }
    else if (ui->generateCharacterButton->isEnabled())
    {
        ui->generateCharacterButton->setEnabled(false);
    }
}

//Generates a new character based on the user's specified race, class, and
//ability scores.
void CharacterGenerator::generateCharacter()
{
    //Builder stuff goes here
    //Get the builder type
    int typeIndex = ui->typeComboBox->currentIndex();

    if (typeIndex == 1)
    {
       setCharacterBuilder(new BruteBuilder);
    }
    else if (typeIndex == 2)
    {
        setCharacterBuilder(new NimbleBuilder);
    }
    else if (typeIndex == 3)
    {
        setCharacterBuilder(new TankBuilder);
    }
    else
    {
        return;
    }

    constructCharacter();

    player()->addObserver(mStatWindow);
    QList<QListWidgetItem *> list = ui->dicerollList->findItems("\\d+", Qt::MatchRegExp);
    QList<short> abilityList;

    foreach(QListWidgetItem* item, list)
    {
        abilityList.append(item->text().toShort());
    }
    mCharacterBuilder->setAbilityScores(abilityList);
    player()->init();

    ui->returnToMenuButton->setEnabled(true);
    ui->saveCharacterButton->setEnabled(true);
}

//Levels up the player, this will level up the class increasing
//both hitpoints and attack bonuses
void CharacterGenerator::returnToMenuButtonPress()
{
    reset();
    if (player() != 0)
    {
        delete mCharacterBuilder;
        mCharacterBuilder = 0;
    }

    Game *game = (Game*)this->parentWidget();
    game->setCurrentIndex(0);
    mStatWindow->hide();
}

void CharacterGenerator::saveCharacter()
{
    QString fileName = QFileDialog::getSaveFileName();

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<<player()->race()<<endl;
    out<<player()->className()<<endl;
    out<<player()->gender()<<endl;
    out<<player()->name()<<endl;
    out<<player()->abilityScore(PlayerCharacter::Strength)<<endl;
    out<<player()->abilityScore(PlayerCharacter::Dexterity)<<endl;
    out<<player()->abilityScore(PlayerCharacter::Constitution)<<endl;
    out<<player()->abilityScore(PlayerCharacter::Intelligence)<<endl;
    out<<player()->abilityScore(PlayerCharacter::Wisdom)<<endl;
    out<<player()->abilityScore(PlayerCharacter::Charisma)<<endl;
    file.close();
}

void CharacterGenerator::setCharacterBuilder(CharacterBuilder *aCharacterBuilder)
{
    if (mCharacterBuilder != 0)
    {
        delete mCharacterBuilder;
        mCharacterBuilder = 0;
    }

    mCharacterBuilder = aCharacterBuilder;
}

PlayerCharacter * CharacterGenerator::player()
{
    if (mCharacterBuilder != 0 && mCharacterBuilder->getPlayer() != 0)
    {
        return mCharacterBuilder->getPlayer();
    }

    return 0;
}

void CharacterGenerator::constructCharacter()
{
    mCharacterBuilder->createNewCharacter(ui->characterName->text(),
                                          ui->genderComboBox->currentText(),
                                          ui->raceComboBox->currentText(),
                                          ui->classComboBox->currentText(),
                                          ui->playerPicture->pixmap()->pixmapData());
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
    ui->generateCharacterButton->setEnabled(false);
    ui->saveCharacterButton->setEnabled(false);
    ui->typeComboBox->setEnabled(false);
}
