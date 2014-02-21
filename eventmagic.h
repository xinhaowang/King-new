#ifndef EVENTMAGIC_H
#define EVENTMAGIC_H

#include <QString>
using namespace std;

class EventMagic
{
public:
    // ****EventMagic's constructors
    EventMagic();
    EventMagic(int tempID, int tempAttackValue,
               int tempType, QString tempName, QString tempUrl);

    // ****EventMagic's accessors
    //EventMagic's ID
    int getID() const;
    void setID(int value);

    // EventMagic's attactValue
    int getAttackValue() const;
    void setAttackValue(int value);

    // EventMagic's Type
    int getType() const;
    void setType(int value);

    // EventMagic's Name
    QString getName() const;
    void setName(const QString &value);

    // EventMagic's Url
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

#endif // EVENTMAGIC_H
