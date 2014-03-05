#ifndef HEX_H
#define HEX_H

#include <QString>

using namespace std;

class Hex
{
public:
    // ****Hex constructor
    Hex();
    Hex(int tempTypeID, QString tempTypeName, QString tempUrl);

    // ****Hex accessors
    int getTypeID() const;
    void setTypeID(int value);

    QString getTypeName() const;
    void setTypeName(const QString &value);

    // Hex Url accessor
    QString getUrl() const;
    void setUrl(const QString &value);



private:
    //define private member
    int TypeID;
    QString TypeName;
    QString Url;
};

#endif // HEX_H
