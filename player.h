#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QList>
#include <QDebug>

#include "thing.h"
#include "hexwidget.h"
#include "building.h"
#include "hero.h"

using namespace std;

//class title for the player
class Player
{
public:
    Player();
    Player(int tempID);

    int getID() const;
    void setID(int value);

    int getGold() const;
    void setGold(int value);

    QList<Thing *> getPlayerThings() const;
    QList<Thing *> getInRackThings() const;
    void setPlayerThings(const QList<Thing *> &value);
    void deletePlayerThings(QList<Thing *> value);
    void deletePlayerThing(Thing *value);
    void setPlayerThing(Thing *value);
    void setAllThingsMovementCount(int count);

    QList<Building *> getPlayerBuildings() const;
    void setPlayerBuildings(const QList<Building *> &value);
    void setPlayerBuilding(Building *value);
    void deleteBuilding(Building *value);

    QList<Hero *> getPlayerHeros() const;
    void setPlayerHero(Hero *value);
    void setPlayerHeros(const QList<Hero *> &value);

    QList<HexWidget *> getPlayerHexs() const;
    void setPlayerHexs(const QList<HexWidget *> &value);
    void setPlayerHex(HexWidget *value);
    void deleteHexWidget(HexWidget *value);

    QString getControlMark() const;
    void setControlMark(const QString &value);

private:
    int ID;                              //Player ID
    int Gold;                            //The Gold that the player currently owned
    QString controlMark;                 //The control mard url for this player
    QList<Thing*> playerThings;         //The Things that the player owned
    QList<Building*> playerBuildings;   //The Forks that the player controled
    QList<Hero*> playerHeros;           //The Heros that the player controled
    QList<HexWidget*> playerHexs;       //The Hexs that the player controled
};

#endif // PLAYER_H
