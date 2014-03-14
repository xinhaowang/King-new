#include "control.h"

Control::Control(QObject *parent):
    QObject(parent)
{
}

Control::~Control()
{

}

//get the random number from 1 to range
int Control::getRandomNumber(int range)
{
    int x = rand() % range + 1;
    return x;
}


/*
 * Accessor for the Thing data
 **/
void Control::initThings()
{
    QFile file(":/ThingsData/test.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",file.errorString());
    }

    QTextStream in(&file);
    while(true)
    {
        QString line = in.readLine();
        if(in.atEnd())
        {
            break;
        }
        QStringList worlds = line.split(",");
        Thing *tempThing = new Thing(worlds.at(0).toInt(), worlds.at(1).toInt(), worlds.at(2).toInt(),
                                     worlds.at(3).toInt(), worlds.at(4), worlds.at(5));
        m_thingData.push_back(tempThing);
    }
    file.close();
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

vector<Thing *> Control::getRandomThingFromNum(int count)
{
    vector<Thing *> temp;
    while(true)
    {
        if(count == 0)
        {
            break;
        } else {
            int tempNum = getRandomNumber(146) - 1;
            if(m_thingData.at(tempNum)->getUsed())
            {
                //the thing has been used
            } else {
                temp.push_back(m_thingData.at(tempNum));
                m_thingData.at(tempNum)->setUsed(true);
                count--;
            }
        }
    }
    return temp;
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
    player1->setControlMark(":/palyer/image/things/player_battle_building/Thing28.jpg");
    player2->setControlMark(":/palyer/image/things/player_battle_building/Thing27.jpg");
    player3->setControlMark(":/palyer/image/things/player_battle_building/Thing30.jpg");
    player4->setControlMark(":/palyer/image/things/player_battle_building/Thing31.jpg");
    m_playerData.push_back(player1);
    m_playerData.push_back(player2);
    m_playerData.push_back(player3);
    m_playerData.push_back(player4);
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
    Hex *hex1 = new Hex(1,"sea",":/hex/image/hex/Sea.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
    Hex *hex2 = new Hex(2,"desert",":/hex/image/hex/Desert.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
    Hex *hex3 = new Hex(3,"forest",":/hex/image/hex/Forest.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
    Hex *hex4 = new Hex(4,"frozen waste",":/hex/image/hex/Frozen_waste.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
    Hex *hex5 = new Hex(5,"jungle",":/hex/image/hex/Jungle.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
    Hex *hex6 = new Hex(6,"mountain",":/hex/image/hex/Mountain.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
    Hex *hex7 = new Hex(7,"plains",":/hex/image/hex/Plains.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
    Hex *hex8 = new Hex(8,"swamp",":/hex/image/hex/Swamp.png",":/hex/image/hex/green.jpg",":/hex/image/hex/red.jpg");
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

/*
 * Accessor for the Building data
 **/
void Control::initBuilding()
{
    Building *building1 = new Building(1, 1, ":/buildings/image/things/player_battle_building/Thing41.jpg");
    Building *building2 = new Building(2, 2, ":/buildings/image/things/player_battle_building/Thing43.jpg");
    Building *building3 = new Building(3, 3, ":/buildings/image/things/player_battle_building/Thing45.jpg");
    Building *building4 = new Building(4, 4, ":/buildings/image/things/player_battle_building/Thing47.jpg");
    m_building.push_back(building1);
    m_building.push_back(building2);
    m_building.push_back(building3);
    m_building.push_back(building4);
}

vector<Building *> Control::building() const
{
    return m_building;
}

Building* Control::getBuildingFromID(int buildingID) const
{
    for(size_t i = 0; i< m_building.size(); i++)
    {
        if(m_building.at(i)->getID() == buildingID)
        {
            return m_building.at(i);
        }
    }
}

void Control::setBuilding(const vector<Building *> &building)
{
    m_building = building;
}

/*
 * Accessor for the hero data
 **/
void Control::initHero()
{
    QFile file(":/ThingsData/hero.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"error",file.errorString());
    }

    QTextStream in(&file);
    while(true)
    {
        QString line = in.readLine();
        if(in.atEnd())
        {
            break;
        }
        QStringList worlds = line.split(",");
        Hero *tempHero = new Hero(worlds.at(0).toInt(), worlds.at(1).toInt(), worlds.at(2).toInt(),
                                    worlds.at(3), worlds.at(4));
        m_heroData.push_back(tempHero);
    }
    file.close();
}
