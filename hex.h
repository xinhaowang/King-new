#ifndef HEX_H
#define HEX_H

#include <QString>
#include "thing.h"

using namespace std;

class Hex
{
public:
    // ****Hex constructor
    Hex();
    Hex(int tempTypeID, QString tempTypeName, QString tempUrl, QString tempGreen, QString tempRed);

    // ****Hex accessors
    int getTypeID() const;
    void setTypeID(int value);

    QString getTypeName() const;
    void setTypeName(const QString &value);

    // Hex Url accessor
    QString getUrl() const;
    void setUrl(const QString &value);

    QString getGreenUrl() const;
    void setGreenUrl(const QString &value);

    QString getRedUrl() const;
    void setRedUrl(const QString &value);

private:
    //define private member
    int TypeID;
    QString TypeName;
    QString Url;
    QString greenUrl;
    QString redUrl;
};

#endif // HEX_H
