#ifndef HEXWIDGET_H
#define HEXWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QMessageBox>
#include "ThingMimeData.h"
#include "hex.h"
#include "mylabel.h"
#include "building.h"
#include "herolabel.h"

class HexWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HexWidget(QWidget *parent = 0);
    HexWidget(QWidget *parent, Hex *tempHex);

    void refreshMyLabel();
    int getID() const;
    void setID(int value);

    bool getIsEnableDrag() const;
    void setIsEnableDrag(bool value);

    bool getIsEnabledClick() const;
    void setIsEnabledClick(bool value);

    int getSelectState() const;
    void setSelectState(int value);

    Building *building() const;
    void setBuilding(Building *building);
    void deleteBuilding();

    QList<mylabel *> thingsLabel() const;
    void setThingsLabel(mylabel *thingsLabel);
    void deleteThingsLabel(QList<mylabel *> tempthingsLabel);
    void deleteAllThingsLabel();
    void returnAllThings();
    void setPlayerThing(QList<Thing *> tempThings, int playerID);
    void setPlayerThing(Thing *tempThings, int playerID);


    Hex *hexData() const;
    void setHexData(Hex *hexData);

    HeroLabel *heroLabel() const;
    void setHeroLabel(HeroLabel *heroLabel);
    void deleteHeroLabel();

    void Message(QString title, QString body);
    QList<mylabel *> getPlayerThingsLabel(int playerID);

    bool getBattle() const;
    void setBattle(bool value);

    void initialControlMark(QString url, int PlayerID);
    void deleteControlMark();
    void initialBuildingLabel(Building *tempbuilding);
    void deleteBuildingLabel();
    void initialNeutralizedBuilidng(Building *tempbuilding);

protected:
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);    
    void paintEvent(QPaintEvent *);

signals:
    void hexHasChangedSignal(HexWidget *tempHexWidget);
    void requirePlayerIDnPhaseSignal();
    void setBulidngSingal(HexWidget*);
    void setHeroSignal(HexWidget*);
    void setThingsToMoveWidgetSignal(HexWidget*);
    void sendThingsBackToHex(const QList<Thing*>);
    void sendbackThingSignal(Thing *tempThing);
    void sendbackOneThingSignal(Thing*);
    void refreshMapClickState(HexWidget*);
    void startCombatSignal(HexWidget*);
    void refrshThingRack();
    void startConstrction(HexWidget*);
    void startSpecialPowerSingal(HexWidget*);
    void checkHeroOwner(HexWidget*);

public slots:
    void setPlayerIDnPhaseSlot(int tempPlayerID, int tempPhase);

private:
    int                 ID;
    int                 playerID;
    int                 phase;
    int                 SelectState;
    bool                isEnableDrag;
    bool                isEnabledClick;
    bool                battle;
    Hex                 *m_hexData;
    QList<mylabel *>    m_thingsLabel;
    Building            *m_building;
    HeroLabel           *m_heroLabel;
    QLabel              *control_mark;
    QLabel              *building_Label;
};

#endif // HEXWIDGET_H
