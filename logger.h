#ifndef LOGGER_H
#define LOGGER_H
#include <QString>
#include <QWidget>
#include <QStackedWidget>
#include <QCloseEvent>
#include <iostream>
using namespace std;

namespace Ui {
    class Logger;
}

class Logger : public QWidget
{
    Q_OBJECT

public:
    explicit Logger(QWidget *parent = 0);
    ~Logger();
    void addLogEntry(QString aString);

private:
    Ui::Logger *ui;

private slots:
};

#endif // LOGGER_H

