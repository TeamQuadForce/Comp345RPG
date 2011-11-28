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
    mMapObject = 0;

}

MapGenerator::~MapGenerator()
{
    delete mMapObject;
    delete ui;
    mMapGrid.clear();
}

//  Initializes signal and slot connections for the GUI
void MapGenerator::init()
{
    mGridLayout = new QGridLayout();
    mGridLayout->setSpacing(0);
    mGridLayout->setVerticalSpacing(0);

    mIntValidator = new QIntValidator(1, 10, this);

    ui->widthLineEdit->setValidator(mIntValidator);
    ui->heightLineEdit->setValidator(mIntValidator);

    connect(ui->generateMapButton, SIGNAL(clicked()), SLOT(generateMap()));
    connect(ui->clearMapButton, SIGNAL(clicked()), SLOT(clearMap()));
    connect(ui->mapElementsButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(selectMapElement(QAbstractButton*)));
    connect(ui->displayMapButton, SIGNAL(clicked()), SLOT(displayMapObject()));
    connect(ui->saveMapButton, SIGNAL(clicked()), SLOT(saveMap()));
    connect(ui->loadMapButton, SIGNAL(clicked()), SLOT(loadMap()));
    connect(ui->returnToMenuButton, SIGNAL(clicked()), SLOT(returnToMenuButtonPress()));
    connect(ui->arenaButton, SIGNAL(clicked()), SLOT(loadArena()));

    ui->chestButton->click(); // Default map element that is selected, put after connect so signal triggers method
    ui->displayMapButton->setVisible(false);
}

//  SLOT METHODS
//  Identifies which radio button is selected in the Map Elements group box
void MapGenerator::selectMapElement(QAbstractButton* button)
{
    if (button->text().compare("Remove") == 0)
        mSelectedMapElement = "";
    else if (button->text().compare("Character") == 0)
        mSelectedMapElement = QString("You");
    else
        mSelectedMapElement = button->text();

}

//  Adds the map element onto the map grid and in the map object
void MapGenerator::addMapElement(QAbstractButton* button)
{
    QTextStream cout(stdout, QIODevice::WriteOnly);

    QString hiddenCoordinates = button->objectName();
    QStringList decipherCoordinates = hiddenCoordinates.split("_");
    if(decipherCoordinates.size() != 2)
    {
        std::cout << "Something's wrong... there are " << decipherCoordinates.size() << " coordinates";
        exit(0);
    }

    int aRowPosition = decipherCoordinates.takeFirst().toInt();
    int aColumnPosition = decipherCoordinates.takeFirst().toInt();
    int charOrExitRowPosition;
    int charOrExitColumnPosition;

    TileSet modifiedTile = mMapObject->mapGridTileSet(aRowPosition, aColumnPosition);
    modifiedTile.setGamePiece(mSelectedMapElement);
    modifiedTile.setIsTerrain(true);
    if(mSelectedMapElement.compare("Wall") == 0)
    {
        modifiedTile.setIsTerrain(false);
    }
    else if(mSelectedMapElement.compare("You") == 0)
    {
        TileSet aCharacterTileSet = mMapObject->characterTileSet();
        if(mMapObject->isCharacterPlaced())
        {
            charOrExitRowPosition = aCharacterTileSet.rowPosition();
            charOrExitColumnPosition = aCharacterTileSet.columnPosition();
            aCharacterTileSet.setGamePiece("");
            mMapObject->setTileSet(aCharacterTileSet, charOrExitRowPosition, charOrExitColumnPosition);
            mMapGrid[charOrExitRowPosition][charOrExitColumnPosition]->setText("");
            mMapGrid[charOrExitRowPosition][charOrExitColumnPosition]->setStyleSheet("background-color: white;");

        }
        mMapObject->setCharacterTileSet(modifiedTile);
        mMapObject->setIsCharacterPlaced(true);
    }
    else if(mSelectedMapElement.compare("Exit") == 0)
    {
        TileSet aExitTileSet = mMapObject->exitTileSet();
        if(mMapObject->isExitPlaced())
        {

            charOrExitRowPosition = aExitTileSet.rowPosition();
            charOrExitColumnPosition = aExitTileSet.columnPosition();
            mMapObject->setTileSet(TileSet(charOrExitRowPosition, charOrExitColumnPosition, true, ""),
                                  charOrExitRowPosition, charOrExitColumnPosition);
            mMapGrid[charOrExitRowPosition][charOrExitColumnPosition]->setText("");
            mMapGrid[charOrExitRowPosition][charOrExitColumnPosition]->setStyleSheet("background-color: white;");

        }
        mMapObject->setExitTileSet(modifiedTile);
        mMapObject->setIsExitPlaced(true);
    }
    else if(mSelectedMapElement.compare("Remove") == 0)
    {
        if(modifiedTile.getGamePiece().compare("You") == 0)
        {
            mMapObject->setIsCharacterPlaced(false);
        }
        else if(modifiedTile.getGamePiece().compare("Exit") == 0)
        {
            mMapObject->setIsExitPlaced(false);
        }

    }


    mMapObject->setLastModifiedTile(modifiedTile);
    mMapObject->setTileSet(modifiedTile, aRowPosition, aColumnPosition);
    mMapObject->notifyObservers();
}

//  Generates the map grid in the GUI
void MapGenerator::generateMap()
{
    statusMessage(QString("Generating map...")); // if this isn't here, a weird bug pops up
    clearMap();

    mMapObject = new Map();
    mWidth = validateWidth(ui->widthLineEdit->text().toInt());
    mHeight = validateHeight(ui->heightLineEdit->text().toInt());

    mMapObject->setMapWidth(mWidth);
    mMapObject->setMapHeight(mHeight);


    mMapObject->createMapGrid();

    mMapObject->addObserver(this);
    mMapObject->notifyObservers();
}

//  Clears the map and deletes the map object
void MapGenerator::clearMap()
{
    if (mGridLayout->count() > 0) {

        // Removing all the items on the GUI map grid
        while(mGridLayout->count() > 0) {
            QWidget* widget = mGridLayout->itemAt(0)->widget();
            mGridLayout->removeWidget(widget);
            delete widget;
        }

        // Disconnecting the connection for buttons in the GUI map grid
        disconnect(mMapGridElements, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(addMapElement(QAbstractButton*)));

        // Clearing the map object's map grid
        mMapObject->clearMapGrid();

        if (mMapObject != 0)
        {
            delete mMapObject;
            mMapObject = 0;
        }
        mMapGrid.clear();
        ui->mapLevelLabel->setText("0");

        statusMessage(QString("Cleared map" + mGridLayout->count()));
    }
}

//  The update method from the Observer pattern. Updates the GUI when a change has been
//  made in the map object
void MapGenerator::update(Observable *aObs)
{
    Map *aMap = (Map*)aObs;

    if(mGridLayout->count() == 0)
    {
        mMapGridElements = new QButtonGroup(ui->mapGeneratorFrame);
        for (int row = 0; row < aMap->mapHeight(); row++)
        {
            mMapGrid.append(QList<QPushButton*>() );
            for (int column = 0; column < aMap->mapWidth(); column++)
            {
                mMapGrid[row].append(new QPushButton(aMap->mapGridTileSet(row, column).getGamePiece()));
                mMapGrid[row][column]->setObjectName(QString::number(row)+"_"+QString::number(column));
                mMapGrid[row][column]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                mMapGrid[row][column]->setStyleSheet(mapStyleSheet(aMap->mapGridTileSet(row, column)));
                mMapGridElements->addButton(mMapGrid[row][column]);
                //                connect(mapGrid[row][column], SIGNAL(clicked()), SLOT(addMapElement()));
                mGridLayout->addWidget(mMapGrid[row][column], row, column);
            }
        }

        connect(mMapGridElements, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(addMapElement(QAbstractButton*)));
        ui->mapGeneratorFrame->setLayout(mGridLayout);
        statusMessage(QString("Created map"));
    }



    TileSet tile = mMapObject->lastModifiedTileSet();

    if (tile.rowPosition() < mMapObject->mapWidth() && tile.columnPosition() < mMapObject->mapHeight())
    {
        mMapGrid[tile.rowPosition()][tile.columnPosition()]->setText(tile.getGamePiece());
        mMapGrid[tile.rowPosition()][tile.columnPosition()]->setStyleSheet(mapStyleSheet(tile));

    }

    if (mMapObject->level() > 0)
    {
        ui->mapLevelLabel->setText(QString::number(mMapObject->level()));
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
    mMapObject->displayMap();
}

void MapGenerator::saveMap()
{
    if (mMapObject == 0)
    {
        return;
    }
    mMapObject->saveMap();
}

void MapGenerator::loadMap()
{
    clearMap();
    mMapObject = new Map();
    mMapObject->loadMap();
    mMapObject->addObserver(this);
    mMapObject->notifyObservers();
}

void MapGenerator::returnToMenuButtonPress()
{
    clearMap();

    if (mMapObject != 0)
    {
        delete mMapObject;
        mMapObject = 0;
    }
    Game *game = (Game*)this->parentWidget();
    game->setCurrentIndex(0);
}

QString MapGenerator::mapStyleSheet(TileSet aTile)
{
    QString styleSheet = "";
    if(aTile.getGamePiece() == "Wall")
    {
        styleSheet = QString("background-color: grey;");
    }
    else if(aTile.getGamePiece() == "Chest")
    {
        styleSheet = QString("background-color: yellow;");
    }
    else if(aTile.getGamePiece() == "Monster")
    {
        styleSheet = QString("background-color: red;");
    }
    else if(aTile.getGamePiece() == "Exit")
    {
        styleSheet = QString("background-color: black;");
    }
    else if(aTile.getGamePiece() == "You")
    {
        styleSheet = QString("background-color: blue;");
    }
    else if(aTile.getGamePiece() == "")
    {
        styleSheet = QString("background-color: white;");
    }
    return styleSheet;
}

void MapGenerator::loadArena()
{
    clearMap();

    MapDirector mapDirector;
    mMapBuilder = new Arena;

    mapDirector.setMapBuilder(mMapBuilder);
    mapDirector.constructMap();

    mMapObject = mapDirector.map()->map();
    mMapObject->setMapWidth(9);
    mMapObject->setMapHeight(9);

    mMapObject->addObserver(this);
    mMapObject->notifyObservers();

}
