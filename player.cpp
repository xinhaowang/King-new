#include "player.h"

Player::Player()
{
}

Player::Player(int tempID)
{
    ID = tempID;
    Gold = 0;
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

void Player::deletePlayerThings(QList<Thing *> value)
{
    for(int i = 0; i < value.size(); i++)
    {
        value.at(i)->setUsed(false);
        value.at(i)->setInRack(true);
        for(vector<Thing*>::iterator iter = playerThings.begin();
            iter != playerThings.end();)
        {
            if(value.at(i) == *iter)
            {
                qDebug() << 1;
                playerThings.erase(iter);
            } else {
                iter++;
            }
        }
    }
    qDebug() << playerThings.size();
}

void Player::setPlayerThing(Thing *value)
{
    playerThings.push_back(value);
}
vector<Building *> Player::getPlayerBuildings() const
{
    return playerBuildings;
}

void Player::setPlayerBuildings(const vector<Building *> &value)
{
    playerBuildings = value;
}

void Player::setPlayerBuilding(Building *value)
{
    playerBuildings.push_back(value);
}

vector<Hero *> Player::getPlayerHeros() const
{
    return playerHeros;
}

void Player::setPlayerHero(Hero *value)
{
    playerHeros.push_back(value);
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
QString Player::getControlMark() const
{
    return controlMark;
}

void Player::setControlMark(const QString &value)
{
    controlMark = value;
}













