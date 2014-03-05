#include "hex.h"

Hex::Hex()
{
}

Hex::Hex(int tempTypeID, QString tempTypeName, QString tempUrl)
{
    TypeID = tempTypeID;
    TypeName = tempTypeName;
    Url = tempUrl;
}

QString Hex::getUrl() const
{
    return Url;
}

void Hex::setUrl(const QString &value)
{
    Url = value;
}
int Hex::getTypeID() const
{
    return TypeID;
}

void Hex::setTypeID(int value)
{
    TypeID = value;
}
QString Hex::getTypeName() const
{
    return TypeName;
}

void Hex::setTypeName(const QString &value)
{
    TypeName = value;
}





