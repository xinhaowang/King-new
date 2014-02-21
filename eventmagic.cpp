#include "eventmagic.h"

EventMagic::EventMagic()
{
}
int EventMagic::getID() const
{
    return ID;
}

void EventMagic::setID(int value)
{
    ID = value;
}
int EventMagic::getAttackValue() const
{
    return attackValue;
}

void EventMagic::setAttackValue(int value)
{
    attackValue = value;
}
int EventMagic::getType() const
{
    return Type;
}

void EventMagic::setType(int value)
{
    Type = value;
}
QString EventMagic::getName() const
{
    return Name;
}

void EventMagic::setName(const QString &value)
{
    Name = value;
}
QString EventMagic::getUrl() const
{
    return Url;
}

void EventMagic::setUrl(const QString &value)
{
    Url = value;
}





