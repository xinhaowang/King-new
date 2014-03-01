#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QFile>
#include <vector>
#include <QMimeData>
#include <QDebug>
#include "thing.h"

using namespace std;

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    ~Control();
    //function for things' operation
    void init();
    void addThing(Thing *tempThing);
    void deleteThing(int thingID);
    void deleteThing(Thing* tempThing);
    void changeIconMode(int mode);
    size_t getSize() {  return m_thingData.size(); }
    Thing *getThing(int index);
    Thing *getThingFromID(int thingID);

signals:

public slots:

private:
    vector<Thing*> m_thingData;

};

class ThingMimeData:public QMimeData
{
    Q_OBJECT
public:
    ThingMimeData():QMimeData()
    {
        m_thingDragList = NULL;
    }

    ~ThingMimeData()
    {
        if(m_thingDragList)
        {
            delete m_thingDragList;
        }
    }

    void setDragDatas(QString mimeType, QList<Thing*> *tempThingList)
    {
        m_format << mimeType;
        m_thingDragList = tempThingList;
    }

    QStringList formats() const
    {
        return m_format;
    }

    const QList<Thing*>* thingDragData() const
    {
        return m_thingDragList;
    }

protected:
    QVariant retrieveData(const QString &mimetype, QVariant::Type preferredType) const
    {
        if(mimetype == "ThingMimeData")
        {
            return m_thingDragList;
        } else {
            return QMimeData::retrieveData(mimetype,preferredType);
        }
    }


private:
    QStringList             m_format;
    const QList<Thing*>     *m_thingDragList;
};

#endif // CONTROL_H
