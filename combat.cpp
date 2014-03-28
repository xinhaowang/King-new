#include "combat.h"
#include "ui_combat.h"

Combat::Combat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Combat)
{
    ui->setupUi(this);
}

Combat::~Combat()
{
    delete ui;
}

void Combat::startCombatSlot()
{
    //begin the combat
    qDebug() << 1;
    qDebug() << "playeronethings " << PlayerOneThing.size();
    qDebug() << "playertwothings " << PlayerTwoThing.size();
    qDebug() << "playerthreethings " << PlayerThreeThing.size();
    qDebug() << "playerfourthings " << PlayerFourThing.size();
}

void Combat::startExplorationSlot()
{
    qDebug() << 2;
    qDebug() << "playeronethings " << PlayerOneThing.size();
    qDebug() << "playertwothings " << PlayerTwoThing.size();
    qDebug() << "playerthreethings " << PlayerThreeThing.size();
    qDebug() << "playerfourthings " << PlayerFourThing.size();
}

void Combat::getBuildingFromHexSlot(Building *tempBuilding)
{
    HexBuilding = tempBuilding;
}

QList<int> Combat::detectWhichPlayer()
{
    QList<int> temp;
    if(PlayerOneThing.size() != 0)
    {
        temp.push_back(1);
    }
    if(PlayerTwoThing.size() != 0)
    {
        temp.push_back(2);
    }
    if(PlayerThreeThing.size() != 0)
    {
        temp.push_back(3);
    }
    if(PlayerFourThing.size() != 0)
    {
        temp.push_back(4);
    }
    return temp;
}

void Combat::getThingFromHexSlot(QList<Thing *> tempThings, int playerID)
{
    //initial the things to the Combat widget
    switch (playerID) {
    case 1:
        PlayerOneThing = tempThings;
        break;
    case 2:
        PlayerTwoThing = tempThings;
        break;
    case 3:
        PlayerThreeThing = tempThings;
        break;
    case 4:
        PlayerFourThing = tempThings;
        break;
    default:
        break;
    }
}

