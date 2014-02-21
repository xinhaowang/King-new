#include "thing.h"

Thing::Thing()
{
}
int Thing::getID() const
{
    return ID;
}

void Thing::setID(int value)
{
    ID = value;
}
int Thing::getAttackValue() const
{
    return attackValue;
}

void Thing::setAttackValue(int value)
{
    attackValue = value;
}
int Thing::getTerrainType() const
{
    return terrainType;
}

void Thing::setTerrainType(int value)
{
    terrainType = value;
}
QString Thing::getName() const
{
    return Name;
}

void Thing::setName(const QString &value)
{
    Name = value;
}
Qstring Thing::getUrl() const
{
    return Url;
}

void Thing::setUrl(const Qstring &value)
{
    Url = value;
}





