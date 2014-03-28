#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QList>
#include <QMimeData>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include "thing.h"
#include "hex.h"
#include "player.h"
#include "hero.h"

using namespace std;

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    ~Control();
    //function for things' operation
    void initThings();
    void addThing(Thing *tempThing);
    void deleteThing(int thingID);
    void deleteThing(Thing* tempThing);
    void changeIconMode(int mode);
    size_t getSize() {  return m_thingData.size(); }
    QList<Thing*> getAllThings();
    Thing *getThing(int index);
    Thing *getThingFromID(int thingID);
    QList<Thing*> getRandomThingFromNum(int count);
    QList<Thing *> getRandomCreatureFromNum(int count);
    //function for players' operation
    void initPlayers();
    Player *getPlayerFromID(int playerID);
    void addHexWidget(HexWidget *tempHexWidget, int playerID);
    //function for hexs' operation
    void initHex();
    QList<Hex *> hex() const;
    void setHex(const QList<Hex *> &hex);
    QList<Hex *> get37hex() const;
    void set37hex(const QList<Hex *> &temp37hex);
    void init37hex();
    //function for buildings' operation
    void initBuilding();
    QList<Building *> building() const;
    void setBuilding(const QList<Building *> &building);
    Building *getBuildingFromID(int buildingID) const;
    //fucntion for heros' operation
    void initHero();
    QList<Hero *> heroData() const;
    void setHeroData(const QList<Hero *> &heroData);
    void chooseTenRandomHeros();
    QList<Hero *> get10heroData() const;
    void set10heroData(const QList<Hero *> &temp10heroData);
    void removeHeroFromID(int heroID);


signals:

public slots:   

private:
    QList<Thing *>      m_thingData;
    QList<Player *>     m_playerData;
    QList<Hex *>        m_hex;
    QList<Hex *>        m_37hex;
    QList<Building *>   m_building;
    QList<Hero *>        m_heroData;
    QList<Hero *>        m_10heroData;

    int getRandomNumber(int range);
};

#endif // CONTROL_H
