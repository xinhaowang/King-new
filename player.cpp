#include "player.h"

Player::Player()
{
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
vector<Thing> Player::getPlayerThings() const
{
    return playerThings;
}

void Player::setPlayerThings(const vector<Thing> &value)
{
    playerThings = value;
}
vector<Building> Player::getPlayerBuildings() const
{
    return playerBuildings;
}

void Player::setPlayerBuildings(const vector<Building> &value)
{
    playerBuildings = value;
}
vector<EventMagic> Player::getPlayerEVMA() const
{
    return playerEVMA;
}

void Player::setPlayerEVMA(const vector<EventMagic> &value)
{
    playerEVMA = value;
}
vector<Hero> Player::getPlayerHeros() const
{
    return playerHeros;
}

void Player::setPlayerHeros(const vector<Hero> &value)
{
    playerHeros = value;
}
vector<Hex> Player::getPlayerHexs() const
{
    return playerHexs;
}

void Player::setPlayerHexs(const vector<Hex> &value)
{
    playerHexs = value;
}







