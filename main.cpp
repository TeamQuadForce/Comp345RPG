#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QObject>
#include <QHBoxLayout>
#include "charactergenerator.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *mainGameWindow = new Game;
    CharacterGenerator *charGen = new CharacterGenerator(mainGameWindow);
    charGen->init();
    mainGameWindow->insertWidget(1, charGen);

    //Move the window to the vertical center, 1/4 from the left side of the screen
    QRect screenRect;
    screenRect = QApplication::desktop()->availableGeometry(mainGameWindow);
    mainGameWindow->move(QPoint(screenRect.center().x(), screenRect.center().y()) - mainGameWindow->rect().center());

    mainGameWindow->show();

    return a.exec();
}
