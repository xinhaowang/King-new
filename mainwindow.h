#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTime>
#include "mapwidget.h"
#include "herowidget.h"
#include "hexwidget.h"
#include "control.h"
#include "dicewidget.h"
#include "selectgoldwidget.h"
#include "thingsdropwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setBackground();
    ~MainWindow();
    int getPlayerTurn() const;
    void setPlayerTurn(int value);
    int getPhaseTurn() const;
    void setPhaseTurn(int value);
    void setThingsRack();
    void initData();
    void initMap();
    void initGlodnTower();
    void startInitMap();
    QRect getMapRect(int index);
    QList<int> getNearHex(int index);
    void initThing();
    void startCollectGold(int count);
    void refreshPlayerGold();    
    void startChooseHero(int count);
    void setHeroWidget();
    void checkOwnHero(int dicevalue);
    void enablePlayerMapClick();
    void Message(QString title, QString body);
    void startRecruitThings(int count);
    void freeRecruitThings();
    void paidRecruitThings();
    int getselectedGold() const;
    void tradeThings();
    void initAllWidget();
    void startMovement(int count);
    void enableNearHexDrag(int hexID);
    void enablePlayerMapDrag();
    void disableMapDrag();
    void resetAllThingMovementCount();
    void deleteAllSeaHex();
    void startCombat(int count);
    void enableCombatHexClick();
    void checkExploration(int diceValue);
    void combatTest();
    void startConstruction(int count);
    int checkTotalCitadelNumber();
    int checkPlayerCitadel(int playerID);
    void changePlayerOrder();
public slots:
    void hexHasChangedSlot(HexWidget *tempHexWidget);
    void refreshThingWidget();
    void getRequirePlayerIDnPhaseSlot();
    void changePlayerTurnSlot(QAbstractButton *);
    void changePlayerTurnSlot2(QAbstractButton *);
    void buttonSlot();
    void setBuildingToHexSlot(HexWidget *tempHexWidget);
    void initThingSlot();
    void confirmThingSlot();
    void startDragSlot(QList<mylabel *>);
    void collectGoldSLOT();
    void chooseHeroSLOT();
    void heroConfirmSlot(Hero *tempHero);
    void updateDiceValueSlot(int tempdiceValue);
    void setHeroSlot(HexWidget *tempHexWidget);
    void getSelectedGoldSlot(int gold);
    void dropboxSlot(QList<Thing *> tempThings);
    void tradeboxSlot(QList<Thing *> tempThings);
    void tradeAndDropThingsSlot();
    void confirmPaidRecruitThingsSlot();
    void skipRecruitHeroSlot();
    void getHexForMoveWidgetSlot(HexWidget *tempHex);
    void movePhaseStartDragSlot(QList<mylabel *> tempLabel);
    void sendbackThingToRackSlot(Thing *tempThing);
    void finishedMovementSlot();
    void sendbackThingToHexSlot(const QList<Thing *> tempThing);
    void sendbackOneThingToHexSlot(Thing *tempThing);
    void refreshClickStateSlot(HexWidget *tempwidget);
    void startCombatSlot(HexWidget *tempHex);
    void getThingsFromRetreatSlot(QList<Thing *> tempThings, int playerID);
    void getThingsFromCombatWinnerSlot(QList<Thing *> tempThings, int playerID);
    void getBuildingFromCombatSlot(Building *tempBuilding, int playerID);
    void changeNextPlayerSlot();
    void startConstructionSlot(HexWidget *tempHex);
    void constrcutionSkipSlot();
    void confirmUseTreasure(mylabel *tempLabel);
signals:
    void initThingToRackSignal(QList<Thing*> m_thingData);
    void sendPlayerIDnPhaseSignal(int tempPlayerID, int tempPhase);
    void initHeroToWidget(QList<Hero*> herolist);
    void initThingsToMovementWidget(QList<Thing*>);
    void sendThingToCombatSignal(QList<Thing*>,int PlayerID);
    void sendBuildingToCombatSignal(Building*);
    void sendOwnerToCombatSignal(int);
    void startCombatSignal(bool);
private:
    Ui::MainWindow       *ui;
    Control              *GameData;
    Hero                 *temp_hero;
    MapWidget            *Things_rack;
    MapWidget            *MovementWidget;
    QPushButton          *button;
    DiceWidget           *dice;
    SelectGoldWidget     *selectedGold;
    HeroWidget           *Hero_widget;
    QList<HexWidget*>    m_hexWidget;
    HexWidget            *selectedHex;
    ThingsDropWidget     *DropBoxWidget;
    ThingsDropWidget     *TradeBoxWidget;
    int                  hexOwnPlayer;
    int                  temp_selectedGold;
    int                  playerTurn;
    int                  PhaseTurn;
    bool                  KeepOneTurn;

    int getRandomNumber(int range);
    void popMessageBox(int index);
    void disableMapClickandDrag();
};

#endif // MAINWINDOW_H
