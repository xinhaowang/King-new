#include "thing.h"

Thing::Thing()
{
}

Thing::Thing(int tempID, int tempAttackValue, int tempType, int tempTerrainType, QString tempName, QString tempUrl):
    inRack(true),used(false)
{
    ID = tempID;
    attackValue = tempAttackValue;
    Type = tempType;
    mode = BigIcon_Mode;
    Url = tempUrl;
    Name = tempName;
    terrainType = tempTerrainType;
    //initial the Qimage for the thing
    image = QImage(tempUrl);
    //each things have four movement count
    movementCount = 4;
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
QString Thing::getUrl() const
{
    return Url;
}

void Thing::setUrl(const QString &value)
{
    Url = value;
}

QImage Thing::getImage() const
{
    return image;
}

void Thing::setImage(const QImage &value)
{
    image = value;
}
bool Thing::getInRack() const
{
    return inRack;
}

void Thing::setInRack(bool value)
{
    inRack = value;
}
bool Thing::getUsed() const
{
    return used;
}

void Thing::setUsed(bool value)
{
    used = value;
}

int Thing::getType() const
{
    return Type;
}

void Thing::setType(int value)
{
    Type = value;
}
int Thing::getMode() const
{
    return mode;
}

void Thing::setMode(int value)
{
    mode = value;
}
int Thing::getMovementCount() const
{
    return movementCount;
}

void Thing::setMovementCount(int value)
{
    movementCount = value;
}













