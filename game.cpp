#include <QDialog>
#include <QDebug>
#include <QHBoxLayout>
#include "game.h"
#include "ui_game.h"
#include "charactergenerator.h"
#include "quitdialog.h"
#include <QSound>

Game::Game(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    QObject::connect(ui->characterGenButton, SIGNAL(released()), SLOT(showCharacterGenPage()));
    QObject::connect(ui->mapGenButton, SIGNAL(clicked()), SLOT(showMapGenPage()));
    QObject::connect(ui->playGenButton, SIGNAL(clicked()), SLOT(showPlayGenPage()));
    this->setCurrentIndex(0);
}

Game::~Game()
{
    delete ui;
}

void Game::showCharacterGenPage()
{

    this->setCurrentIndex(1);
    ((CharacterGenerator*)this->currentWidget())->show();
    this->resize(this->currentWidget()->size());

}

void Game::showMapGenPage()
{
    this->setCurrentIndex(2);
    this->resize(this->widget(2)->size());
}

void Game::showPlayGenPage()
{
    this->setCurrentIndex(3);
    this->resize(this->widget(3)->size());
}

void Game::closeEvent(QCloseEvent *event)
{
    QuitDialog *quitDialog = new QuitDialog;
    int quit = quitDialog->exec();
    delete quitDialog;
    if (quit == 1)
    {
        qApp->quit();
    }
    else
    {
        event->ignore();
    }
}
