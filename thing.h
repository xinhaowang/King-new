#ifndef THING_H
#define THING_H

#include <QString>
#include <QDebug>
#include <QImage>

using namespace std;

enum {BigIcon_Mode = 0, SmallIcon_Mode};

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
    QString getUrl() const;
    void setUrl(const QString &value);

    // private members
    int getMode() const;
    void setMode(int value);

    QImage getImage() const;
    void setImage(const QImage &value);

private:
    int ID;
    int attackValue;
    int Type;
    int terrainType;
    int mode;
    QString Name;
    QString Url;
    QImage image;
};

#endif // THING_H
