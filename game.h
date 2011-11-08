#ifndef GAME_H
#define GAME_H

#include <QStackedWidget>
#include <QCloseEvent>

namespace Ui {
    class Game;
}

class Game : public QStackedWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

private:
    Ui::Game *ui;

private slots:
    void showCharacterGenPage();
    void closeEvent(QCloseEvent *event);
};

#endif // GAME_H
