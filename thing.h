#ifndef THING_H
#define THING_H

#include <QString>
using namespace std;

class Thing
{
public:
    //**** Thing's constructor
    Thing();
    Thing(int tempID, int tempAttackValue, int tempType,
          int tempTerrainType, QString tempName, QString tempUrl);

    //**** Thing's accessors
    // Thing's ID
    int getID() const;
    void setID(int value);

    // Thing's attackValue
    int getAttackValue() const;
    void setAttackValue(int value);

    // Thing's terrainType
    int getTerrainType() const;
    void setTerrainType(int value);

    // Thing's Name
    QString getName() const;
    void setName(const QString &value);

    // Thing's Url
    Qstring getUrl() const;
    void setUrl(const Qstring &value);

// private members
private:
    int ID;
    int attackValue;
    int Type;
    int terrainType;
    QString Name;
    Qstring Url;
};

#endif // THING_H
