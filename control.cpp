#include "control.h"

Control::Control(QObject *parent):
    QObject(parent)
{
}

Control::~Control()
{

}

/*
 * General accessor for the Control
 **/

/*
 * Accessor for the Thing data
 **/
void Control::initThings()
{
    Thing *tempThing1 = new Thing(1,3,1,1,"hello",":/creatures/image/things/desert/Thing98.jpg");
    Thing *tempThing2 = new Thing(2,3,1,1,"hello",":/creatures/image/things/desert/Thing99.jpg");
    Thing *tempThing3 = new Thing(3,3,1,1,"hello",":/creatures/image/things/desert/Thing100.jpg");
    Thing *tempThing4 = new Thing(4,3,1,1,"hello",":/creatures/image/things/desert/Thing101.jpg");
    Thing *tempThing5 = new Thing(5,3,1,1,"hello",":/creatures/image/things/desert/Thing102.jpg");
    Thing *tempThing6 = new Thing(6,3,1,1,"hello",":/creatures/image/things/desert/Thing103.jpg");
    Thing *tempThing7 = new Thing(7,3,1,1,"hello",":/creatures/image/things/desert/Thing104.jpg");
    Thing *tempThing8 = new Thing(8,3,1,1,"hello",":/creatures/image/things/desert/Thing105.jpg");
    Thing *tempThing9 = new Thing(9,3,1,1,"hello",":/creatures/image/things/desert/Thing106.jpg");
    Thing *tempThing10 = new Thing(10,3,1,1,"hello",":/creatures/image/things/desert/Thing107.jpg");
    m_thingData.push_back(tempThing1);
    m_thingData.push_back(tempThing2);
    m_thingData.push_back(tempThing3);
    m_thingData.push_back(tempThing4);
    m_thingData.push_back(tempThing5);
    m_thingData.push_back(tempThing6);
    m_thingData.push_back(tempThing7);
    m_thingData.push_back(tempThing8);
    m_thingData.push_back(tempThing9);
    m_thingData.push_back(tempThing10);

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

void Control::changeIconMode(int mode)
{
    for(size_t i = 0; i < m_thingData.size(); i++)
    {
        m_thingData[i]->setMode(mode);
    }
}

vector<Thing *> Control::getAllThings()
{
    return m_thingData;
}

Thing *Control::getThing(int index)
{
    if ((index >= 0) && (index < m_thingData.size()))
    {
        return m_thingData[index];
    }
}


/*
 * Accessor for the Player data
 **/
void Control::initPlayers()
{
    Player *player1 = new Player(1);
    Player *player2 = new Player(2);
    Player *player3 = new Player(3);
    Player *player4 = new Player(4);
    m_playerData.push_back(player1);
    m_playerData.push_back(player2);
    m_playerData.push_back(player3);
    m_playerData.push_back(player4);

    //test
    player1->setPlayerThings(m_thingData);
}

Player *Control::getPlayerFromID(int playerID)
{
    for(size_t i = 0; i < m_playerData.size(); i++)
    {
        if(playerID == m_playerData[i]->getID())
        {
            return m_playerData[i];
        }
    }
}

//add the Hex widget to the new player
void Control::addHexWidget(HexWidget *tempHexWidget, int playerID)
{
    m_playerData.at(playerID - 1)->setPlayerHex(tempHexWidget);
}

/*
 * Accessor for the Hex data
 **/
void Control::initHex()
{
    Hex *hex1 = new Hex(1,"sea",":/hex/image/hex/Sea.png");
    Hex *hex2 = new Hex(2,"desert",":/hex/image/hex/Desert.png");
    Hex *hex3 = new Hex(3,"forest",":/hex/image/hex/Forest.png");
    Hex *hex4 = new Hex(4,"frozen waste",":/hex/image/hex/Frozen_waste.png");
    Hex *hex5 = new Hex(5,"jungle",":/hex/image/hex/Jungle.png");
    Hex *hex6 = new Hex(6,"mountain",":/hex/image/hex/Mountain.png");
    Hex *hex7 = new Hex(7,"plains",":/hex/image/hex/Plains.png");
    Hex *hex8 = new Hex(8,"swamp",":/hex/image/hex/Swamp.png");
    m_hex.push_back(hex1);
    m_hex.push_back(hex2);
    m_hex.push_back(hex3);
    m_hex.push_back(hex4);
    m_hex.push_back(hex5);
    m_hex.push_back(hex6);
    m_hex.push_back(hex7);
    m_hex.push_back(hex8);
}

vector<Hex *> Control::hex() const
{
    return m_hex;
}

void Control::setHex(const vector<Hex *> &hex)
{
    m_hex = hex;
}

