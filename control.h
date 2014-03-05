#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QFile>
#include <vector>
#include <QMimeData>
#include <QDebug>
#include "thing.h"
#include "hex.h"
#include "player.h"

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
    //function for players' operation
    void initPlayers();
    Player *getPlayerFromID(int playerID);
    void addHexWidget(HexWidget *tempHexWidget, int playerID);
    //function for hexs' operation
    void initHex();
    vector<Hex *> hex() const;
    void setHex(const vector<Hex *> &hex);

signals:

public slots:   

private:
    vector<Thing*>  m_thingData;
    vector<Player*> m_playerData;
    vector<Hex*>    m_hex;
};

#endif // CONTROL_H
