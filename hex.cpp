#include "hex.h"

Hex::Hex()
{
}
int Hex::getID() const
{
    return ID;
}

void Hex::setID(int value)
{
    ID = value;
}
int Hex::getType() const
{
    return Type;
}

void Hex::setType(int value)
{
    Type = value;
}
QString Hex::getUrl() const
{
    return Url;
}

void Hex::setUrl(const QString &value)
{
    Url = value;
}



