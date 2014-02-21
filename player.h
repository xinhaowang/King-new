#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <vector>
#include <QDebug>

#include "thing.h"
#include "hex.h"
#include "building.h"
#include "eventmagic.h"
#include "hero.h"

using namespace std;

//class title for the player
class Player
{
public:
    Player();

    int getID() const;
    void setID(int value);

    int getGold() const;
    void setGold(int value);

    vector<Thing> getPlayerThings() const;
    void setPlayerThings(const vector<Thing> &value);

    vector<Building> getPlayerBuildings() const;
    void setPlayerBuildings(const vector<Building> &value);

    vector<EventMagic> getPlayerEVMA() const;
    void setPlayerEVMA(const vector<EventMagic> &value);

    vector<Hero> getPlayerHeros() const;
    void setPlayerHeros(const vector<Hero> &value);

    vector<Hex> getPlayerHexs() const;
    void setPlayerHexs(const vector<Hex> &value);

private:
    int ID;                             //Player ID
    int Gold;                           //The Gold that the player currently owned
    vector<Thing> playerThings;         //The Things that the player owned
    vector<Building> playerBuildings;   //The Forks that the player controled
    vector<EventMagic> playerEVMA;      //The Magic and event that the player controled
    vector<Hero> playerHeros;           //The Heros that the player controled
    vector<Hex> playerHexs;             //The Hexs that the player controled
};

#endif // PLAYER_H
