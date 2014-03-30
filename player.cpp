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
QList<Thing *> Player::getPlayerThings() const
{
    return playerThings;
}

QList<Thing *> Player::getInRackThings() const
{
    QList<Thing *> tempThing;
    for(int i = 0; i < playerThings.size(); i++)
    {
        if(playerThings[i]->getInRack())
        {
            tempThing.push_back(playerThings[i]);
        }
    }
    return tempThing;
}

void Player::setPlayerThings(const QList<Thing *> &value)
{
    playerThings = value;
}

void Player::deletePlayerThings(QList<Thing *> value)
{
    for(int i = 0; i < value.size(); i++)
    {
        value.at(i)->setUsed(false);
        value.at(i)->setInRack(true);
        for(int j = 0; j < playerThings.size(); j++)
        {
            if(value.at(i)->getID() == playerThings.at(j)->getID())
            {
                playerThings.removeAt(j);
            }
        }
    }
}

void Player::deletePlayerThing(Thing *value)
{
    for(int i = 0; i < playerThings.size(); i++)
    {
        value->setUsed(false);
        value->setInRack(true);
        if(playerThings.at(i)->getID() == value->getID())
        {
            playerThings.removeAt(i);
        }
    }
}

void Player::setPlayerThing(Thing *value)
{
    playerThings.push_back(value);
}

void Player::setAllThingsMovementCount(int count)
{
    for(int i = 0; i < playerThings.size(); i++)
    {
        playerThings.at(i)->setMovementCount(count);
    }
}
QList<Building *> Player::getPlayerBuildings() const
{
    return playerBuildings;
}

void Player::setPlayerBuildings(const QList<Building *> &value)
{
    playerBuildings = value;
}

void Player::setPlayerBuilding(Building *value)
{
    playerBuildings.push_back(value);
}

QList<Hero *> Player::getPlayerHeros() const
{
    return playerHeros;
}

void Player::setPlayerHero(Hero *value)
{
    playerHeros.push_back(value);
}

void Player::setPlayerHeros(const QList<Hero *> &value)
{
    playerHeros = value;
}
QList<HexWidget *> Player::getPlayerHexs() const
{
    return playerHexs;
}

void Player::setPlayerHexs(const QList<HexWidget *> &value)
{
    playerHexs = value;
}

void Player::setPlayerHex(HexWidget *value)
{
    playerHexs.push_back(value);
}

void Player::deleteHexWidget(HexWidget *value)
{
    playerHexs.removeOne(value);
}
QString Player::getControlMark() const
{
    return controlMark;
}

void Player::setControlMark(const QString &value)
{
    controlMark = value;
}













