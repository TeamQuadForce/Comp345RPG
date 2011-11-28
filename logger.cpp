#include "logger.h"
#include "ui_logger.h"
#include <QDialog>
#include <QDebug>
#include <QHBoxLayout>
#include "game.h"
#include "ui_game.h"
#include "quitdialog.h"

Logger::Logger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logger)
{
    ui->setupUi(this);
}

Logger::~Logger()
{
    delete ui;
}

void Logger::addLogEntry(QString aString){

    ui->log->append(aString);

}
