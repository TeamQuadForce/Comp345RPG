#ifndef STATWINDOW_H
#define STATWINDOW_H

#include <QWidget>
#include "observer.h"

namespace Ui {
    class StatWindow;
}

class StatWindow : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit StatWindow(QWidget *parent = 0);
    ~StatWindow();

    void update(PlayerCharacter *aPlayer);
    void reset();

private:
    Ui::StatWindow *ui;
};

#endif // STATWINDOW_H
