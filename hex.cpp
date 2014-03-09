#include "hex.h"

Hex::Hex()
{
}

Hex::Hex(int tempTypeID, QString tempTypeName, QString tempUrl, QString tempGreen, QString tempRed)
{
    TypeID = tempTypeID;
    TypeName = tempTypeName;
    Url = tempUrl;
    greenUrl = tempGreen;
    redUrl = tempRed;
}

QString Hex::getUrl() const
{
    return Url;
}

void Hex::setUrl(const QString &value)
{
    Url = value;
}
QString Hex::getGreenUrl() const
{
    return greenUrl;
}

void Hex::setGreenUrl(const QString &value)
{
    greenUrl = value;
}
QString Hex::getRedUrl() const
{
    return redUrl;
}

void Hex::setRedUrl(const QString &value)
{
    redUrl = value;
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





