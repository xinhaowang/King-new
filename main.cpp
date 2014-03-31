#include "mainwindow.h"
#include "combat.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //set up the combat widget
    Combat combat;

    //set up the MianWindow
    MainWindow w;

    //set up the connection between combat and mainwindow
    QObject::connect(&w, SIGNAL(sendThingToCombatSignal(QList<Thing*>,int)),
                     &combat, SLOT(getThingFromHexSlot(QList<Thing*>,int)));
    QObject::connect(&w, SIGNAL(sendBuildingToCombatSignal(Building*)),
                     &combat, SLOT(getBuildingFromHexSlot(Building*)));
    QObject::connect(&w, SIGNAL(sendOwnerToCombatSignal(int)),
                     &combat, SLOT(getOwnPlayer(int)));
    QObject::connect(&w, SIGNAL(startCombatSignal(bool)),
                     &combat, SLOT(startCombatSlot(bool)));
    QObject::connect(&combat, SIGNAL(sendCombatWinnerThingSignal(QList<Thing*>,int)),
                     &w, SLOT(getThingsFromCombatWinnerSlot(QList<Thing*>,int)));
    QObject::connect(&combat, SIGNAL(sendRetretThingSignal(QList<Thing*>,int)),
                     &w, SLOT(getThingsFromRetreatSlot(QList<Thing*>,int)));
    QObject::connect(&combat, SIGNAL(sendBuildingToHexSignal(Building*,int)),
                     &w, SLOT(getBuildingFromCombatSlot(Building*,int)));
    QObject::connect(&combat, SIGNAL(changeNextPlayerSingal()),
                     &w, SLOT(changeNextPlayerSlot()));


    w.show();
    return a.exec();
}
