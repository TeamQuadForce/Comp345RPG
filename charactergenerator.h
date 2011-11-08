#ifndef CHARACTERGENERATOR_H
#define CHARACTERGENERATOR_H

#include <QWidget>
#include <QList>

#include "playercharacter.h"
#include "diceroller.h"
#include "observer.h"
#include "statwindow.h"

namespace Ui {
    class CharacterGenerator;
}

class CharacterGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterGenerator(QWidget *parent = 0);
    ~CharacterGenerator();

    void init();
    virtual void show();

private:
    Ui::CharacterGenerator *ui;
    PlayerCharacter *mPlayer;
    StatWindow *mStatWindow;

    void removeLowestValue(QList<int> &aList);

private slots:
    void changePicture();

    void rollAbilityScores();
    void addToStrength();
    void addToDexterity();
    void addToConstitution();
    void addToIntelligence();
    void addToWisdom();
    void addToCharisma();

    void generateCharacter();
    void readyToGenerate();
    void returnToMenuButtonPress();

    void reset();
};

#endif // CHARACTERGENERATOR_H
