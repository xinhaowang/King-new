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
    int x = qrand() % range + 1;
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
   for(int i = 0; i < m_thingData.size(); i++)
   {
        if(m_thingData[i]->getID() == thingID)
        {
            QList<Thing*>::iterator it = m_thingData.begin();
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
        for(int i = 0; i < m_thingData.size(); i++)
        {
            if(m_thingData.at(i) == tempThing)
            {
                m_thingData.removeAt(i);
            }
        }
    }
}

Thing* Control::getThingFromID(int thingID)
{
    if(thingID)
    {
        for(int i = 0; i < m_thingData.size(); i++)
        {
            if(thingID == m_thingData[i]->getID())
            {
                return m_thingData[i];
                break;
            }
        }
    } else {
        return NULL;
    }
}

QList<Thing *> Control::getRandomThingFromNum(int count)
{
    QList<Thing *> temp;
    while(true)
    {
        if(count == 0)
        {
            break;
        } else {
            int tempNum = getRandomNumber(176) - 1;
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

QList<Thing *> Control::getRandomCreatureFromNum(int count)
{
    QList<Thing *> temp;
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
    for(int i = 0; i < m_thingData.size(); i++)
    {
        m_thingData[i]->setMode(mode);
    }
}

QList<Thing *> Control::getAllThings()
{
    return m_thingData;
}

Thing *Control::getThing(int index)
{
    return m_thingData.at(index);
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
    for(int i = 0; i < m_playerData.size(); i++)
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
    Hex *hex1 = new Hex(1,"sea",":/hex/image/hex/Sea.png",":/hex/image/hex/Sea_select.png",":/hex/image/hex/Sea_select.png");
    Hex *hex2 = new Hex(2,"desert",":/hex/image/hex/Desert.png",":/hex/image/hex/Desert_select.png",":/hex/image/hex/Desert_select.png");
    Hex *hex3 = new Hex(3,"forest",":/hex/image/hex/Forest.png",":/hex/image/hex/Forest_select.png",":/hex/image/hex/Forest_select.png");
    Hex *hex4 = new Hex(4,"frozen waste",":/hex/image/hex/Frozen_waste.png",":/hex/image/hex/Frozen_waste_select.png",":/hex/image/hex/Frozen_waste_select.png");
    Hex *hex5 = new Hex(5,"jungle",":/hex/image/hex/Jungle.png",":/hex/image/hex/Jungle_select.png",":/hex/image/hex/Jungle_select.png");
    Hex *hex6 = new Hex(6,"mountain",":/hex/image/hex/Mountain.png",":/hex/image/hex/Mountain_select.png",":/hex/image/hex/Mountain_select.png");
    Hex *hex7 = new Hex(7,"plains",":/hex/image/hex/Plains.png",":/hex/image/hex/Plains_select.png",":/hex/image/hex/Plains_select.png");
    Hex *hex8 = new Hex(8,"swamp",":/hex/image/hex/Swamp.png",":/hex/image/hex/Swamp_select.png",":/hex/image/hex/Swamp_select.png");
    m_hex.push_back(hex1);
    m_hex.push_back(hex2);
    m_hex.push_back(hex3);
    m_hex.push_back(hex4);
    m_hex.push_back(hex5);
    m_hex.push_back(hex6);
    m_hex.push_back(hex7);
    m_hex.push_back(hex8);
}

QList<Hex *> Control::hex() const
{
    return m_hex;
}

void Control::setHex(const QList<Hex *> &hex)
{
    m_hex = hex;
}

QList<Hex *> Control::get37hex() const
{
    return m_37hex;
}

void Control::set37hex(const QList<Hex *> &temp37hex)
{
    m_37hex = temp37hex;
}

void Control::init37hex()
{
//    for(int i = 0; i < 37; i++)
//    {
//        m_37hex.push_back(m_hex.at(getRandomNumber(8) - 1));
//    }
    m_37hex.push_back(m_hex.at(0));
    m_37hex.push_back(m_hex.at(6));
    m_37hex.push_back(m_hex.at(7));
    m_37hex.push_back(m_hex.at(4));
    m_37hex.push_back(m_hex.at(7));
    m_37hex.push_back(m_hex.at(1));
    m_37hex.push_back(m_hex.at(0));
    m_37hex.push_back(m_hex.at(5));
    m_37hex.push_back(m_hex.at(3));
    m_37hex.push_back(m_hex.at(6));
    m_37hex.push_back(m_hex.at(3));
    m_37hex.push_back(m_hex.at(5));
    m_37hex.push_back(m_hex.at(7));
    m_37hex.push_back(m_hex.at(6));
    m_37hex.push_back(m_hex.at(2));
    m_37hex.push_back(m_hex.at(6));
    m_37hex.push_back(m_hex.at(2));
    m_37hex.push_back(m_hex.at(5));
    m_37hex.push_back(m_hex.at(2));
    m_37hex.push_back(m_hex.at(1));
    m_37hex.push_back(m_hex.at(3));
    m_37hex.push_back(m_hex.at(1));
    m_37hex.push_back(m_hex.at(3));
    m_37hex.push_back(m_hex.at(7));
    m_37hex.push_back(m_hex.at(0));
    m_37hex.push_back(m_hex.at(6));
    m_37hex.push_back(m_hex.at(5));
    m_37hex.push_back(m_hex.at(4));
    m_37hex.push_back(m_hex.at(2));
    m_37hex.push_back(m_hex.at(7));
    m_37hex.push_back(m_hex.at(0));
    m_37hex.push_back(m_hex.at(7));
    m_37hex.push_back(m_hex.at(2));
    m_37hex.push_back(m_hex.at(5));
    m_37hex.push_back(m_hex.at(3));
    m_37hex.push_back(m_hex.at(1));
    m_37hex.push_back(m_hex.at(1));
}
/*
 * Accessor for the Building data
 **/
void Control::initBuilding()
{
    Building *building1 = new Building(1, 1, ":/buildings/image/things/player_battle_building/Thing41.jpg",":/buildings/image/things/player_battle_building/Thing42.jpg");
    Building *building2 = new Building(2, 2, ":/buildings/image/things/player_battle_building/Thing43.jpg",":/buildings/image/things/player_battle_building/Thing44.jpg");
    Building *building3 = new Building(3, 3, ":/buildings/image/things/player_battle_building/Thing45.jpg",":/buildings/image/things/player_battle_building/Thing46.jpg");
    Building *building4 = new Building(4, 4, ":/buildings/image/things/player_battle_building/Thing47.jpg",":/buildings/image/things/player_battle_building/Thing48.jpg");
    m_building.push_back(building1);
    m_building.push_back(building2);
    m_building.push_back(building3);
    m_building.push_back(building4);
}

QList<Building *> Control::building() const
{
    return m_building;
}

Building* Control::getBuildingFromID(int buildingID) const
{
    for(int i = 0; i< m_building.size(); i++)
    {
        if(m_building.at(i)->getID() == buildingID)
        {
            return m_building.at(i);
        }
    }
}

void Control::setBuilding(const QList<Building *> &building)
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
QList<Hero *> Control::heroData() const
{
    return m_heroData;
}

void Control::setHeroData(const QList<Hero *> &heroData)
{
    m_heroData = heroData;
}

void Control::chooseTenRandomHeros()
{
    QList<Hero *> temp = m_heroData;
    QList<int> tempint;
    //add the master thief to the data
    tempint.push_back(4);
    while(true){
        int random = getRandomNumber(22) - 1;
        if(tempint.empty())
        {
            tempint.push_back(random);
            continue;
        }
        bool same = false;
        for(int i = 0; i < tempint.size(); i++)
        {
            if(random == tempint.at(i))
            {
                same = true;
            }
        }
        if(same)
        {
            continue;
        } else {
            tempint.push_back(random);
            if(tempint.size() == 10)
            {
                break;
            }
        }
    }
    for(int i = 0; i < tempint.size(); i++)
    {
        m_10heroData.push_back(temp.at(tempint.at(i)));
    }
}
QList<Hero *> Control::get10heroData() const
{
    return m_10heroData;
}

void Control::addHeroTo10HeroData(Hero *tempHero)
{
    m_10heroData.push_back(tempHero);
}

void Control::removeHeroFromID(int heroID)
{
    for(int i = 0; i < m_10heroData.size(); i++)
    {
        if(heroID == m_10heroData.at(i)->getID())
        {
            m_10heroData.removeAt(i);
            break;
        }
    }
}

void Control::set10heroData(const QList<Hero *> &temp10heroData)
{
    m_10heroData = temp10heroData;
}

