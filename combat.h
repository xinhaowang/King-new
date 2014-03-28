#ifndef COMBAT_H
#define COMBAT_H

#include <QWidget>
#include <QList>
#include <QButtonGroup>
#include "control.h"

namespace Ui {
class Combat;
}

class Combat : public QWidget
{
    Q_OBJECT

public:
    explicit Combat(QWidget *parent = 0);
    ~Combat();

    QList<int> detectWhichPlayer();
public slots:
    void getThingFromHexSlot(QList<Thing*> tempThings, int playerID);
    void getBuildingFromHexSlot(Building *tempBuilding);
    void startExplorationSlot();
    void startCombatSlot();
private:
    Ui::Combat *ui;
    Building        *HexBuilding;
    Hero            *HexHero;
    QList<Thing*>   PlayerOneThing;
    QList<Thing*>   PlayerTwoThing;
    QList<Thing*>   PlayerThreeThing;
    QList<Thing*>   PlayerFourThing;

};

#endif // COMBAT_H
