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

    QGridLayout *layout;
    QIntValidator *intValidator;
    QList<QList<QPushButton*> > mapGrid;
    QString mapElementSelected;
    Map *mapObject;
    QButtonGroup *mapGridElements;
    int width, height;

    void statusMessage(QString aString);

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

    void returnToMenuButtonPress();
};

#endif // MAPGENERATOR_H
