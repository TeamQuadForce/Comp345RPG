#ifndef DUNGEON_H
#define DUNGEON_H

#include <QWidget>
#include <Qlist>
#include <map.h>
#include <QAbstractButton>
#include <QGridLayout>
#include <QPushButton>


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

    QString mapStyleSheet(TileSet aTile);
private:
    Ui::Dungeon *ui;
    void initializeMap();
    Map *mapObject;
    QGridLayout *layout;
    QList<QList<QPushButton*> > mapGrid;

private slots:
    void moveCharacter(QAbstractButton *button);
};

#endif // DUNGEON_H
