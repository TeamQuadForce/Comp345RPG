#include "mapgenerator.h"
#include "ui_mapgenerator.h"
#include "game.h"
#include <QFile>
#include <QTextStream>
#include <iostream>


MapGenerator::MapGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapGenerator)
{
    ui->setupUi(this);
    mapObject = 0;

}

MapGenerator::~MapGenerator()
{
    delete mapObject;
    delete ui;
    mapGrid.clear();
}

//  Initializes signal and slot connections for the GUI
void MapGenerator::init()
{
    layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setVerticalSpacing(0);

    intValidator = new QIntValidator(1, 10, this);

    ui->widthLineEdit->setValidator(intValidator);
    ui->heightLineEdit->setValidator(intValidator);

    connect(ui->generateMapButton, SIGNAL(clicked()), SLOT(generateMap()));
    connect(ui->clearMapButton, SIGNAL(clicked()), SLOT(clearMap()));
    connect(ui->mapElementsButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(selectMapElement(QAbstractButton*)));
    connect(ui->displayMapButton, SIGNAL(clicked()), SLOT(displayMapObject()));
    connect(ui->saveMapButton, SIGNAL(clicked()), SLOT(saveMap()));
    connect(ui->loadMapButton, SIGNAL(clicked()), SLOT(loadMap()));
    connect(ui->returnToMenuButton, SIGNAL(clicked()), SLOT(returnToMenuButtonPress()));

    ui->chestButton->click(); // Default map element that is selected, put after connect so signal triggers method

}

//  SLOT METHODS
//  Identifies which radio button is selected in the Map Elements group box
void MapGenerator::selectMapElement(QAbstractButton* button)
{
    mapElementSelected = button->text();
}

//  Adds the map element onto the map grid and in the map object
void MapGenerator::addMapElement(QAbstractButton* button)
{
    QString hiddenCoordinates = button->objectName();
    QStringList decipherCoordinates = hiddenCoordinates.split("_");
    if(decipherCoordinates.size() != 2)
    {
        std::cout << "Something's wrong... there are " << decipherCoordinates.size() << " coordinates";
        exit(0);
    }

    int aRowPosition = decipherCoordinates.takeFirst().toInt();
    int aColumnPosition = decipherCoordinates.takeFirst().toInt();


    TileSet modifiedTile = mapObject->tileSet(aRowPosition, aColumnPosition);

    if (mapElementSelected != modifiedTile.getGamePiece())
    {
        modifiedTile.setGamePiece(mapElementSelected);
    }

    mapObject->setTileSet(modifiedTile);
    mapObject->setTileSet(modifiedTile, aRowPosition, aColumnPosition);
    mapObject->notifyObservers();
}

//  Generates the map grid in the GUI
void MapGenerator::generateMap()
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << "omg";
    statusMessage(QString("Generating map...")); // if this isn't here, a weird bug pops up
    if (layout->count() > 0 )
    {
        clearMap();
    }

    mapObject = new Map();
    width = validateWidth(ui->widthLineEdit->text().toInt());
    height = validateHeight(ui->heightLineEdit->text().toInt());

    mapObject->setMapWidth(width);
    mapObject->setMapHeight(height);


    mapObject->createMapGrid();

    mapObject->addObserver(this);
    mapObject->notifyObservers();
}

//  Clears the map and deletes the map object
void MapGenerator::clearMap()
{
    while(layout->count() > 0) {
        QWidget* widget = layout->itemAt(0)->widget();
        layout->removeWidget(widget);
        delete widget;
    }
    disconnect(mapGridElements, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(addMapElement(QAbstractButton*)));

    mapObject->clearMapGrid();

    if (mapObject != 0)
    {
        delete mapObject;
        mapObject = 0;
    }

    for (int row=0; row<mapGrid.size() ; row++)
    {
        mapGrid[row].clear();
    }
    mapGrid.clear();
    statusMessage(QString("Cleared map" + layout->count()));
}

//  The update method from the Observer pattern. Updates the GUI when a change has been
//  made in the map object
void MapGenerator::update(Observable *aObs)
{
    Map *aMap = (Map*)aObs;

    if(layout->count() == 0)
    {
        mapGridElements = new QButtonGroup(ui->mapGeneratorFrame);
        for (int row = 0; row < aMap->mapHeight(); row++)
        {
            mapGrid.append(QList<QPushButton*>() );
            for (int column = 0; column < aMap->mapWidth(); column++)
            {
                mapGrid[row].append(new QPushButton(aMap->tileSet(row, column).getGamePiece()));
                mapGrid[row][column]->setObjectName(QString::number(row)+"_"+QString::number(column));
                mapGrid[row][column]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                mapGridElements->addButton(mapGrid[row][column]);
//                connect(mapGrid[row][column], SIGNAL(clicked()), SLOT(addMapElement()));
                layout->addWidget(mapGrid[row][column], row, column);
            }
        }

        connect(mapGridElements, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(addMapElement(QAbstractButton*)));
        ui->mapGeneratorFrame->setLayout(layout);
        statusMessage(QString("Created map"));
    }



    TileSet tile = mapObject->tileSet();

    if (tile.rowPosition() < mapObject->mapWidth() && tile.columnPosition() < mapObject->mapHeight())
    {
        mapGrid[tile.rowPosition()][tile.columnPosition()]->setText(tile.getGamePiece());
    }


}

//  Generates a status message in the statusTextEdit box
void MapGenerator::statusMessage(QString aString)
{
    ui->statusTextEdit->setText(ui->statusTextEdit->toPlainText() + "\n" + aString);
}

//  Validates the map's height entry and sets a default size if it's the entry was not valid
int MapGenerator::validateHeight(int aHeight)
{
    int mapHeight = aHeight;

    if (mapHeight < 5)
    {
        mapHeight = 5;
        statusMessage(QString("Default height"));
        ui->heightLineEdit->setText(QString("5"));
    }
    return mapHeight;
}

//  Validates the map's width entry and sets a default size if it's the entry was not valid
int MapGenerator::validateWidth(int aWidth)
{
    int mapWidth = aWidth;
    if (mapWidth < 5)
    {
        mapWidth = 5;
        statusMessage(QString("Default width"));
        ui->widthLineEdit->setText(QString("5"));
    }

    return mapWidth;
}

void MapGenerator::displayMapObject()
{
    mapObject->displayMap();
}

void MapGenerator::saveMap()
{
    if (mapObject == 0)
    {
        return;
    }
    mapObject->saveMap();
}

void MapGenerator::loadMap()
{
    if (layout->count() > 0 )
    {
        clearMap();
    }
    mapObject = new Map();
    mapObject->loadMap();
    mapObject->addObserver(this);
    mapObject->notifyObservers();
}

void MapGenerator::returnToMenuButtonPress()
{
    if (mapObject != 0)
    {
        delete mapObject;
        mapObject = 0;
    }
    Game *game = (Game*)this->parentWidget();
    game->setCurrentIndex(0);
}
