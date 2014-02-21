#include "hero.h"

Hero::Hero()
{
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




