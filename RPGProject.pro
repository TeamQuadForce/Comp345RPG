#-------------------------------------------------
#
# Project created by QtCreator 2011-10-13T20:08:16
#
#-------------------------------------------------

QT       += core gui

TARGET = RPGAssignment2
TEMPLATE = app

INCLUDEPATH +=  Character \
                CharacterGenerator \
                Chest \
                Equipment \
                Map \
                MapGenerator \
                Monster \
                PlayGenerator

include(Character/Character.pri)
include(CharacterGenerator/CharacterGenerator.pri)
include(Chest/Chest.pri)
include(Equipment/Equipment.pri)
include(Map/Map.pri)
include(Monster/Monster.pri)
include(MapGenerator/MapGenerator.pri)
include(PlayGenerator/PlayGenerator.pri)

SOURCES += main.cpp \
    diceroller.cpp \
    game.cpp \
    quitdialog.cpp

HEADERS  += \
    diceroller.h \
    observable.h \
    observer.h \
    game.h \
    quitdialog.h

FORMS    += game.ui \
    quitdialog.ui

RESOURCES += \
    resources.qrc
