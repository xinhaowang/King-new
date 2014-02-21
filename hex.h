#ifndef HEX_H
#define HEX_H

#include <QString>
using namespace std;

class Hex
{
public:
    // ****Hex constructor
    Hex();
    Hex(int tempID, int tempType, QString tempUrl);

    // ****Hex accessors
    // Hex ID accessor
    int getID() const;
    void setID(int value);

    // Hex Type accessor
    int getType() const;
    void setType(int value);

    // Hex Url accessor
    QString getUrl() const;
    void setUrl(const QString &value);

private:
    //define private member
    int ID;
    int Type;
    QString Url;
};

#endif // HEX_H
