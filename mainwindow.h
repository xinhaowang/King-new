#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
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
    QRect getMapRect(int index);

public slots:
    void hexHasChangedSlot(HexWidget *tempHexWidget);
    void getRequirePlayerIDSlot();

signals:
    void initThingToRackSignal(vector<Thing*> m_thingData);
    void sendPlayerIDSignal(int tempPlayerID);

private:
    Ui::MainWindow       *ui;
    MapWidget            *Things_rack;
    Control              *GameData;
    vector<HexWidget*>   m_hexWidget;
    int                  playerTurn;
    int                  PhaseTurn;

    int getRandomNumber(int range);
};

#endif // MAINWINDOW_H
