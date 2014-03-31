#ifndef COMBAT_H
#define COMBAT_H

#include <QWidget>
#include <QList>
#include <QGroupBox>
#include <QtGui>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include "control.h"
#include "dicewidget.h"

namespace Ui {
class Combat;
}

class Combat : public QWidget
{
    Q_OBJECT

public:
    explicit Combat(QWidget *parent = 0);
    ~Combat();

    QList<int> detectWhichPlayer();
    void initialLayout();
    Thing *getThingFromID(int thingID);
    int getCombatTurn() const;
    void setCombatTurn(int value);
    int getPlayerTurn() const;
    void setPlayerTurn(int value);
    void popMessageBox();
    void removePlayerThingFromID(int thingID);
    QList<Thing *> getThingsFromPlayerID(int playerID);
    void Message(QString title, QString body);
    bool checkAllPlayerRack();
    Building *getHexBuilding() const;
    void setHexBuilding(Building *value);
    int getBuildingValue() const;
    void setBuildingValue(int value);
    void deleteALLWidget();
public slots:
    void getThingFromHexSlot(QList<Thing*> tempThings, int playerID);
    void getBuildingFromHexSlot(Building *tempBuilding);
    void getOwnPlayer(int Player);
    void startCombatSlot(bool Combat);
    void updateDiceValueSlot(int tempDice);
    void buttonClickedSlot();
    void changePlayerTurnSlot(QAbstractButton *temp);
    void continueButtonSlot();
    void retreatButtonSlot();
    void buildingButtonClickSlot();
signals:
    void sendRetretThingSignal(QList<Thing*>, int);
    void sendCombatWinnerThingSignal(QList<Thing*>,int);
    void sendBuildingToHexSignal(Building*,int);
    void changeNextPlayerSingal();
private:
    Ui::Combat *ui;
    int             ownPlayer;
    int             playerTurn;
    int             combatTurn;
    int             diceValue;
    int             buildingValue;
    bool            rollDice;
    bool            isCombat;
    QPushButton     *button;
    QPushButton     *button2;
    QPushButton     *buildingButton;
    QList<int>      playerCount;
    QList<QLabel*>  playerHitPoint;
    QLabel          *playerTurnLabel;
    DiceWidget      *dice;
    Building        *HexBuilding;
    QWidget         *globalWidget;
    QGridLayout     *vertical_layout;
    QGroupBox       *createPlayerBox(QList<Thing *> tempThings, int PlayerID);
    QList<Thing*>   PlayerOneThing;
    QList<Thing*>   PlayerTwoThing;
    QList<Thing*>   PlayerThreeThing;
    QList<Thing*>   PlayerFourThing;

};

#endif // COMBAT_H
