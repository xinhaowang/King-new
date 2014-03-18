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
    void refreshThingWidget();
    void startChooseHero(int count);
    void setHeroWidget();
    void checkOwnHero(int dicevalue);
    void enablePlayerMapClick();
    void Message(QString title, QString body);
public slots:
    void hexHasChangedSlot(HexWidget *tempHexWidget);
    void getRequirePlayerIDnPhaseSlot();
    void changePlayerTurnSlot(QAbstractButton *);
    void changePlayerTurnSlot2(QAbstractButton *);

    void buttonSlot();
    void setBuildingToHexSlot(HexWidget *tempHexWidget);    

    void initThingSlot();
    void confirmThingSlot();
    void startDragSlot();

    void collectGoldSLOT();
    void chooseHeroSLOT();

    void heroConfirmSlot(Hero *tempHero);
    void updateDiceValueSlot(int tempdiceValue);
    void setHeroSlot(HexWidget *tempHexWidget);
    void getSelectedGoldSlot(int gold);
signals:
    void initThingToRackSignal(vector<Thing*> m_thingData);
    void sendPlayerIDnPhaseSignal(int tempPlayerID, int tempPhase);
    void initHeroToWidget(QList<Hero*> herolist);

private:
    Ui::MainWindow       *ui;
    Control              *GameData;

    Hero                 *temp_hero;
    int                  temp_selectedGold = 0;
    MapWidget            *Things_rack;
    QPushButton          *button;
    DiceWidget           *dice;
    SelectGoldWidget     *selectedGold;
    HeroWidget           *Hero_widget;
    vector<HexWidget*>   m_hexWidget;
    int                  playerTurn;
    int                  PhaseTurn;

    int getRandomNumber(int range);
    void popMessageBox(int index);
    void disableMapClick();
};

#endif // MAINWINDOW_H
