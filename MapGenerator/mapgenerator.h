#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QIntValidator>
#include <QButtonGroup>
#include <QPushButton>
#include <QString>

#include "map.h"
#include "observer.h"
#include "MapBuilder.h"
#include "MapDirector.h"
#include "arena.h"

namespace Ui {
    class MapGenerator;
}

class MapGenerator : public QWidget, public Observer
{
    Q_OBJECT


public:
    explicit MapGenerator(QWidget *parent = 0);
    ~MapGenerator();
    void init();
    void update(Observable *aObs);


private:
    Ui::MapGenerator *ui;

    QGridLayout *mGridLayout;
    QIntValidator *mIntValidator;
    QList<QList<QPushButton*> > mMapGrid;
    QString mSelectedMapElement;
    Map *mMapObject;
    QButtonGroup *mMapGridElements;
    int mWidth;
    int mHeight;
    MapBuilder *mMapBuilder;
    bool mIsArena;

    void statusMessage(QString aString);
    QString mapStyleSheet(TileSet aTile);
    int validateHeight(int aHeight);
    int validateWidth(int aWidth);



private slots:
    void displayMapObject();
    void generateMap();
    void clearMap();
    void selectMapElement(QAbstractButton* button);
    void addMapElement(QAbstractButton* button);
    void saveMap();
    void loadMap();
    void loadArena();
    void returnToMenuButtonPress();
};

#endif // MAPGENERATOR_H
