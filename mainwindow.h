#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <stdio.h>
#include <windows.h>
#include "mapwidget.h"
#include "hexwidget.h"
#include "control.h"

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

signals:
    void initThingToRackSignal(vector<Thing*> m_thingData);
    void sendPlayerIDnPhaseSignal(int tempPlayerID, int tempPhase);

private:
    Ui::MainWindow       *ui;
    MapWidget            *Things_rack;
    Control              *GameData;
    QPushButton          *button;
    vector<HexWidget*>   m_hexWidget;
    int                  playerTurn;
    int                  PhaseTurn;

    int getRandomNumber(int range);
    void popMessageBox(int index);
    void disableMapClick();
};

#endif // MAINWINDOW_H
