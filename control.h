#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QFile>
#include <QList>
#include <vector>
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
    vector<Thing*> getAllThings();
    Thing *getThing(int index);
    Thing *getThingFromID(int thingID);
    vector<Thing*> getRandomThingFromNum(int count);
    //function for players' operation
    void initPlayers();
    Player *getPlayerFromID(int playerID);
    void addHexWidget(HexWidget *tempHexWidget, int playerID);
    //function for hexs' operation
    void initHex();
    vector<Hex *> hex() const;
    void setHex(const vector<Hex *> &hex);    
    vector<Hex *> get37hex() const;
    void set37hex(const vector<Hex *> &temp37hex);
    void init37hex();
    //function for buildings' operation
    void initBuilding();
    vector<Building *> building() const;
    void setBuilding(const vector<Building *> &building);
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
    vector<Thing *>      m_thingData;
    vector<Player *>     m_playerData;
    vector<Hex *>        m_hex;
    vector<Hex *>        m_37hex;
    vector<Building *>   m_building;
    QList<Hero *>        m_heroData;
    QList<Hero *>        m_10heroData;

    int getRandomNumber(int range);
};

#endif // CONTROL_H
