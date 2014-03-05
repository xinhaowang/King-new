#include "player.h"

Player::Player()
{
}

Player::Player(int tempID)
{
    ID = tempID;
}

int Player::getID() const
{
    return ID;
}

void Player::setID(int value)
{
    ID = value;
}
int Player::getGold() const
{
    return Gold;
}

void Player::setGold(int value)
{
    Gold = value;
}
vector<Thing *> Player::getPlayerThings() const
{
    return playerThings;
}

vector<Thing *> Player::getInRackThings() const
{
    vector<Thing *> tempThing;
    for(size_t i = 0; i < playerThings.size(); i++)
    {
        if(playerThings[i]->getInRack())
        {
            tempThing.push_back(playerThings[i]);
        }
    }
    return tempThing;
}

void Player::setPlayerThings(const vector<Thing *> &value)
{
    playerThings = value;
}
vector<Building *> Player::getPlayerBuildings() const
{
    return playerBuildings;
}

void Player::setPlayerBuildings(const vector<Building *> &value)
{
    playerBuildings = value;
}
vector<EventMagic *> Player::getPlayerEVMA() const
{
    return playerEVMA;
}

void Player::setPlayerEVMA(const vector<EventMagic *> &value)
{
    playerEVMA = value;
}
vector<Hero *> Player::getPlayerHeros() const
{
    return playerHeros;
}

void Player::setPlayerHeros(const vector<Hero *> &value)
{
    playerHeros = value;
}
vector<HexWidget *> Player::getPlayerHexs() const
{
    return playerHexs;
}

void Player::setPlayerHexs(const vector<HexWidget *> &value)
{
    playerHexs = value;
}

void Player::setPlayerHex(HexWidget *value)
{
    playerHexs.push_back(value);
}












