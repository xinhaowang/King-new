#ifndef COMBAT_H
#define COMBAT_H

#include <QWidget>
#include <QList>
#include <QGroupBox>
#include <QtGui>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
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
    void initQGroupBox();
    void initialLayout();
public slots:
    void getThingFromHexSlot(QList<Thing*> tempThings, int playerID);
    void getBuildingFromHexSlot(Building *tempBuilding);
    void getOwnPlayer(int Player);
    void startExplorationSlot();
    void startCombatSlot();

private:
    Ui::Combat *ui;
    int             ownPlayer;
    int             playerTurn;
    int             combatTurn;
    Building        *HexBuilding;
    QGroupBox       *createPlayerBox(QList<Thing *> tempThings);
    QList<Thing*>   PlayerOneThing;
    QList<Thing*>   PlayerTwoThing;
    QList<Thing*>   PlayerThreeThing;
    QList<Thing*>   PlayerFourThing;

};

#endif // COMBAT_H
