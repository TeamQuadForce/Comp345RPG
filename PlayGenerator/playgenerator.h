#ifndef PLAYGENERATOR_H
#define PLAYGENERATOR_H
#include <QWidget>
#include <playercharacter.h>
#include <map.h>

namespace Ui {
    class PlayGenerator;
}
class PlayGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit PlayGenerator(QWidget *parent = 0);
    ~PlayGenerator();

private slots:
    void loadCharacter();
    void loadMap();
    void enterDungeon();

private:
    Ui::PlayGenerator *ui;
    PlayerCharacter *mPlayer;
    Map *map;
};

#endif // PLAYGENERATOR_H
