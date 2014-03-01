#include "control.h"

Control::Control(QObject *parent):
    QObject(parent)
{
}

Control::~Control()
{

}

//initiate the control class import the things data
void Control::init()
{

        Thing *tempThing = new Thing();
        tempThing->setName("hello");
        tempThing->setID(1);
        tempThing->setMode(BigIcon_Mode);
        QString iconPath = QString(":/creatures/image/things/desert/Thing%1.jpg").arg(98);
        QFile iconFile(iconPath);
        if(iconFile.exists())
        {
            tempThing->setImage(QImage(iconPath));
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
            m_thingData.push_back(tempThing);
        } else {
            delete tempThing;
        }
}

void Control::addThing(Thing *tempThing)
{
    if(tempThing)
    {
        m_thingData.push_back(tempThing);
    }
}

void Control::deleteThing(int thingID)
{
   for(size_t i = 0; i < m_thingData.size(); i++)
   {
        if(m_thingData[i]->getID() == thingID)
        {
            vector<Thing*>::iterator it = m_thingData.begin();
            it = it + i;
            m_thingData.erase(it);
            break;
        }
   }
}

void Control::deleteThing(Thing *tempThing)
{
    if(tempThing)
    {
        vector<Thing*>::iterator it = m_thingData.begin();
        for(it; it != m_thingData.end(); ++it)
        {
            if(tempThing == *it)
            {
                m_thingData.erase(it);
                break;
            }
        }
    }
}

Thing* Control::getThingFromID(int thingID)
{
    if(thingID)
    {
        for(size_t i = 0; i < m_thingData.size(); i++)
        {
            if(thingID == m_thingData[i]->getID())
            {
                return m_thingData[i];
            }
        }
    }
}

//change all the things' mode
void Control::changeIconMode(int mode)
{
    for(size_t i = 0; i < m_thingData.size(); i++)
    {
        m_thingData[i]->setMode(mode);
    }
}

Thing *Control::getThing(int index)
{
    if ((index >= 0) && (index < m_thingData.size()))
    {
        return m_thingData[index];
    }
}
