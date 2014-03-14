#include "hero.h"

Hero::Hero()
{
}

Hero::Hero(int tempID, int tempAttackValue, int tempType, QString tempName, QString tempUrl)
{
    ID = tempID;
    attackValue = tempAttackValue;
    Type = tempType;
    Name = tempName;
    Url = tempUrl;
}

int Hero::getID() const
{
    return ID;
}

void Hero::setID(int value)
{
    ID = value;
}
int Hero::getAttackValue() const
{
    return attackValue;
}

void Hero::setAttackValue(int value)
{
    attackValue = value;
}
int Hero::getType() const
{
    return Type;
}

void Hero::setType(int value)
{
    Type = value;
}
QString Hero::getName() const
{
    return Name;
}

void Hero::setName(const QString &value)
{
    Name = value;
}
QString Hero::getUrl() const
{
    return Url;
}

void Hero::setUrl(const QString &value)
{
    Url = value;
}
int Hero::getMode() const
{
    return mode;
}

void Hero::setMode(int value)
{
    mode = value;
}





