#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QObject>
#include <QHBoxLayout>
#include "charactergenerator.h"
#include "mapgenerator.h"
#include "game.h"
#include <QSound>
#include "dungeon.h"
#include "playgenerator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *mainGameWindow = new Game;

    QSound intro("sounds/character.wav");
    intro.setLoops( -1 );
    intro.play();
    CharacterGenerator *charGen = new CharacterGenerator(mainGameWindow);
    charGen->init();

    MapGenerator *mapGen = new MapGenerator(mainGameWindow);
    PlayGenerator *playGen = new PlayGenerator(mainGameWindow);
    mapGen->init();

    mainGameWindow->insertWidget(1, charGen);
    mainGameWindow->insertWidget(2, mapGen);
    mainGameWindow->insertWidget(3, playGen);

    //Move the window to the vertical center, 1/4 from the left side of the screen
    QRect screenRect;
    screenRect = QApplication::desktop()->availableGeometry(mainGameWindow);
    mainGameWindow->move(QPoint(screenRect.center().x(), screenRect.center().y()) - mainGameWindow->rect().center());

    mainGameWindow->show();


    return a.exec();
}
