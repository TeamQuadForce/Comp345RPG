#ifndef DUNGEON_H
#define DUNGEON_H

#include <QWidget>
#include <Qlist>
#include <map.h>
#include <QAbstractButton>


namespace Ui {
    class Dungeon;
}

class Dungeon : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit Dungeon(QWidget *parent = 0);
    Dungeon();
    ~Dungeon();

    void init();
    void assignMovementOperations();
    void update(Observable *aObs);

private:
    Ui::Dungeon *ui;
    void initializeMap();
    Map *mapObject;
    QList<QList<QAbstractButton*> > mapGrid;

private slots:
    void moveCharacter(QAbstractButton *button);
};

#endif // DUNGEON_H
