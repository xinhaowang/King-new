#include "building.h"

Building::Building()
{
}
int Building::getIncome() const
{
    return income;
}

void Building::setIncome(int value)
{
    income = value;
}
QString Building::getUrl() const
{
    return Url;
}

void Building::setUrl(const QString &value)
{
    Url = value;
}
int Building::getID() const
{
    return ID;
}

void Building::setID(int value)
{
    ID = value;
}



