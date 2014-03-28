#include "mainwindow.h"
#include "combat.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //set up the MianWindow
    MainWindow w;

    //set up the combat widget
    Combat combat;

    //set up the connection between combat and mainwindow
    QObject::connect(&w, SIGNAL(sendThingToCombatSignal(QList<Thing*>,int)),
                     &combat, SLOT(getThingFromHexSlot(QList<Thing*>,int)));
    QObject::connect(&w, SIGNAL(sendBuildingToCombatSignal(Building*)),
                     &combat, SLOT(getBuildingFromHexSlot(Building*)));
    QObject::connect(&w, SIGNAL(startExploration()),
                     &combat, SLOT(startExplorationSlot()));
    QObject::connect(&w, SIGNAL(startCombatSignal()),
                     &combat, SLOT(startCombatSlot()));

    w.show();
    return a.exec();
}
