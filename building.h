#ifndef BUILDING_H
#define BUILDING_H

#include <QString>
#include <vector>
#include <QDebug>

using namespace std;

// Class title fot the player

class Building
{
public:
    //building's constructor
    Building();
    Building(int tempID, int tempIncome, QString tempUrl);
    
    // building ID accessors
    int getID() const;
    void setID(int value);

private:
    int ID;         //building ID
    int income;     //building income
    QString Url;    //building's Url
    
};

#endif // BUILDING_H
