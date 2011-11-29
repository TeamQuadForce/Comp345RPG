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
    void backToMainScreen();

private:
    Ui::PlayGenerator *ui;
    PlayerCharacter *mPlayer;
    Map *mMap;
    QString filename;
    bool mMapIsArena;
};

#endif // PLAYGENERATOR_H
