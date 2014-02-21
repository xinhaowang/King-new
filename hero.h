#ifndef HERO_H
#define HERO_H

#include <QString>
using namespace std;

class Hero
{
public:
    // ****Hero's constructors
    Hero();
    Hero(int tempID, int tempAttackValue, int tempType,
         QString tempName, QString tempUrl);

    // ****Hero's accessors
    // Hero's ID
    int getID() const;
    void setID(int value);

    // Hero's attackValue
    int getAttackValue() const;
    void setAttackValue(int value);

    // Hero's Type
    int getType() const;
    void setType(int value);

    // Hero's Name
    QString getName() const;
    void setName(const QString &value);

    // Hero's Url
    QString getUrl() const;
    void setUrl(const QString &value);

// private members
private:
    int ID;
    int attackValue;
    int Type;
    QString Name;
    QString Url;
};

#endif // HERO_H
