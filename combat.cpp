#include "combat.h"
#include "ui_combat.h"

Combat::Combat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Combat)
{
    ui->setupUi(this);
    buildingValue = 0;
    HexBuilding = NULL;
    this->setObjectName("Combat");
}

Combat::~Combat()
{

    delete ui;
}

QGroupBox *Combat::createPlayerBox(QList<Thing*> tempThings, int PlayerID)
{
    QString temp = "Player " + QString::number(PlayerID) + " Things";
    QGroupBox *groupBox = new QGroupBox(temp);
    QGridLayout *vbox = new QGridLayout();
    QList<QPushButton*> tempButton;
    for(int i = 0; i < tempThings.size(); i++)
    {
        QPushButton *button = new QPushButton;
        button->setObjectName(QString::number(tempThings.at(i)->getID()));
        QString temp = "border-image: url(" + tempThings.at(i)->getUrl();
        button->setStyleSheet(temp + ")");
        button->setFixedSize(80,80);
        connect(button,SIGNAL(clicked()),this,SLOT(buttonClickedSlot()));
        tempButton.push_back(button);
    }
    for(int i = 0; i < tempButton.size(); i++)
    {
        if(i < 5)
        {
            vbox->addWidget(tempButton.at(i),0,i);
        } else {
            vbox->addWidget(tempButton.at(i),1,i%5);
        }
    }
    groupBox->setObjectName(QString::number(PlayerID));
    groupBox->setLayout(vbox);
    return groupBox;
}

void Combat::buttonClickedSlot()
{
    if(!rollDice)
    {
        //we can apply the hit now
        for(int i = 0; i < playerCount.size(); i++)
        {
            if(getPlayerTurn() == playerCount.at(i))
            {
                int hitPoint = playerHitPoint.at(i)->objectName().toInt();
                //get the button
                QObject *button = sender();
                QWidget *widget = qobject_cast<QWidget *>(button);
                //get the player rack
                QObject *PlayerRack = button->parent();
                int playerWidgetID = PlayerRack->objectName().toInt();
                if(playerWidgetID == getPlayerTurn())
                {
                    Message("Warning", "You can't remove your things");
                } else {
                    //remove the thing and button
                    if(hitPoint == 0)
                    {
                        //not enough hitpoint,change to next player
                        popMessageBox();
                        Message("Warning", "Don't have hitpoint!");
                        break;
                    } else {
                        //remove the things
                        int ThingID = button->objectName().toInt();
                        removePlayerThingFromID(ThingID);
                        //delete the button
                        delete widget;
                        //refresh the playerhitpoint label
                        playerHitPoint.at(i)->setObjectName(QString::number(hitPoint-1));
                        QString temp ="Player " + QString::number(playerCount.at(i)) +  " HitPoint : " + playerHitPoint.at(i)->objectName();
                        playerHitPoint.at(i)->setText(temp);
                        //check if the hitPoint become to 0
                        if((hitPoint == 1)&&!checkAllPlayerRack())
                        {
                            popMessageBox();
                            break;
                        }
                    }
                }
            }
        }

    }

}

int Combat::getPlayerTurn() const
{
    return playerTurn;
}

void Combat::setPlayerTurn(int value)
{
    playerTurn = value;
    QString temp = "Player : " + QString::number(value) + " turn.";
    playerTurnLabel->setText(temp);
}

int Combat::getCombatTurn() const
{
    return combatTurn;
}

void Combat::setCombatTurn(int value)
{
    combatTurn = value;
}

void Combat::removePlayerThingFromID(int thingID)
{
    for(int i = 0; i < PlayerOneThing.size(); i++)
    {
        if(PlayerOneThing.at(i)->getID() == thingID)
        {
            PlayerOneThing.removeAt(i);
            break;
        }
    }
    for(int i = 0; i < PlayerTwoThing.size(); i++)
    {
        if(PlayerTwoThing.at(i)->getID() == thingID)
        {
            PlayerTwoThing.removeAt(i);
            break;
        }
    }
    for(int i = 0; i < PlayerThreeThing.size(); i++)
    {
        if(PlayerThreeThing.at(i)->getID() == thingID)
        {
            PlayerThreeThing.removeAt(i);
            break;
        }
    }
    for(int i = 0; i < PlayerFourThing.size(); i++)
    {
        if(PlayerFourThing.at(i)->getID() == thingID)
        {
            PlayerFourThing.removeAt(i);
            break;
        }
    }
}

Thing *Combat::getThingFromID(int thingID)
{
    for(int i = 0; i < PlayerOneThing.size(); i++)
    {
        if(PlayerOneThing.at(i)->getID() == thingID)
        {
            return PlayerOneThing.at(i);
        }
    }
    for(int i = 0; i < PlayerTwoThing.size(); i++)
    {
        if(PlayerTwoThing.at(i)->getID() == thingID)
        {
            return PlayerTwoThing.at(i);
        }
    }
    for(int i = 0; i < PlayerThreeThing.size(); i++)
    {
        if(PlayerThreeThing.at(i)->getID() == thingID)
        {
            return PlayerThreeThing.at(i);
        }
    }
    for(int i = 0; i < PlayerFourThing.size(); i++)
    {
        if(PlayerFourThing.at(i)->getID() == thingID)
        {
            return PlayerFourThing.at(i);
        }
    }
}

void Combat::initialLayout()
{
    vertical_layout = new QGridLayout;
    playerCount = detectWhichPlayer();
    for(int i = 0; i < playerCount.size(); i++)
    {
        switch (playerCount.at(i)) {
        case 1:
            vertical_layout->addWidget(createPlayerBox(PlayerOneThing,1),i,0);
            break;
        case 2:
            vertical_layout->addWidget(createPlayerBox(PlayerTwoThing,2),i,0);
            break;
        case 3:
            vertical_layout->addWidget(createPlayerBox(PlayerThreeThing,3),i,0);
            break;
        case 4:
            vertical_layout->addWidget(createPlayerBox(PlayerFourThing,4),i,0);
            break;
        default:
            break;
        }
        //initial the hitpoint for each player
        QLabel *hitPoint = new QLabel;
        hitPoint->setObjectName("0");
        QString temp ="Player " + QString::number(playerCount.at(i)) + " HitPoint : " + hitPoint->objectName();
        hitPoint->setText(temp);
        playerHitPoint.push_back(hitPoint);
        vertical_layout->addWidget(hitPoint,i,1);
        //initial the building if owerner have one
        if(ownPlayer == playerCount.at(i))
        {
            if(HexBuilding)
            {

                buildingButton = new QPushButton;
                buildingButton->setObjectName(QString::number(getHexBuilding()->getID()));
                QString temp = "border-image: url(" + getHexBuilding()->getUrl();
                buildingButton->setStyleSheet(temp + ")");
                buildingButton->setFixedSize(80,80);
                connect(buildingButton,SIGNAL(clicked()),this,SLOT(buildingButtonClickSlot()));
                vertical_layout->addWidget(buildingButton,i,2);
                //initial the building value
                buildingValue = getHexBuilding()->getIncome();
            }
        }
    }
    //roll the dice first
    rollDice = true;
    //initial the dice widget
    dice = new DiceWidget(this);
    vertical_layout->addWidget(dice,0,3);
    dice->setFixedSize(100,100);
    connect(dice, SIGNAL(updateDiceValueSignal(int)), this, SLOT(updateDiceValueSlot(int)));
    dice->show();
    //set the player turn label
    playerTurnLabel = new QLabel;
    playerTurnLabel->setStyleSheet("background-color: white;");
    setPlayerTurn(playerCount.at(0));
    vertical_layout->addWidget(playerTurnLabel,0,4);
    //initial the button
    button = new QPushButton;
    button2 = new QPushButton;
    button->setText("Continue");
    button2->setText("Retreats");
    vertical_layout->addWidget(button,1,3);
    vertical_layout->addWidget(button2,1,4);
    connect(button,SIGNAL(clicked()),this,SLOT(continueButtonSlot()));
    connect(button2,SIGNAL(clicked()),this,SLOT(retreatButtonSlot()));
    button->hide();
    button2->hide();
    //add the globalwidget
    globalWidget = new QWidget(this);
    globalWidget->setLayout(vertical_layout);
}

void Combat::buildingButtonClickSlot()
{
    //when we want eliminate the buidling
    if(!rollDice)
    {
        if(getPlayerTurn() == ownPlayer)
        {
            Message("Warning", "You can't remove your things");
        } else {
            for(int i = 0; i < playerCount.size(); i++)
            {
                if(getPlayerTurn() == playerCount.at(i))
                {
                    int hitPoint = playerHitPoint.at(i)->objectName().toInt();
                    if(hitPoint == 0)
                    {
                        Message("Warning", "Don't have hitpoint!");
                        popMessageBox();
                    } else {
                        if(getBuildingValue() == 0)
                        {
                            Message("Warning", "Building is neutral");
                        } else {
                            //reduce one level of the building
                            setBuildingValue(getBuildingValue()-1);
                            //refresh the playerhitpoint label
                            playerHitPoint.at(i)->setObjectName(QString::number(hitPoint-1));
                            QString temp ="Player " + QString::number(playerCount.at(i)) +  " HitPoint : " + playerHitPoint.at(i)->objectName();
                            playerHitPoint.at(i)->setText(temp);
                            //check if the building value become to 0
                            if(getBuildingValue() == 0)
                            {
                                //change the building to nertral
                                QString temp = "border-image: url(" + getHexBuilding()->getNeutralURL();
                                buildingButton->setStyleSheet(temp + ")");
                            }
                            //check for winning the game
                            checkAllPlayerRack();
                        }
                    }
                }
            }
        }
    }
}

int Combat::getBuildingValue() const
{
    return buildingValue;
}

void Combat::setBuildingValue(int value)
{
    buildingValue = value;
}

void Combat::continueButtonSlot()
{
    //change to next player, do nothing
    popMessageBox();
}

void Combat::deleteALLWidget()
{
    //refresh all the combatdata
    for(int i = 0; i < playerCount.size(); i++)
    {
        qDeleteAll(vertical_layout->itemAtPosition(i,0)->widget()->children());
        delete vertical_layout->itemAtPosition(i,0)->widget();
    }
    PlayerOneThing.clear();
    PlayerTwoThing.clear();
    PlayerThreeThing.clear();
    PlayerFourThing.clear();
    playerCount.clear();
    qDeleteAll(playerHitPoint);
    playerHitPoint.clear();
    delete playerTurnLabel;
    delete globalWidget;
    HexBuilding = NULL;
}

void Combat::retreatButtonSlot()
{
    //retreat
    if(isCombat)
    {
        for(int i = 0; i < playerCount.size(); i++)
        {
            if(getPlayerTurn() == playerCount.at(i))
            {
                //clear the widget
                qDeleteAll(vertical_layout->itemAtPosition(i,0)->widget()->children());
                delete vertical_layout->itemAtPosition(i,0)->widget();
                //special income and building can't send back
                //send back all the other creature
                QList<Thing*> result;
                for(int j = 0; j < getThingsFromPlayerID(getPlayerTurn()).size();)
                {
                    if(getThingsFromPlayerID(getPlayerTurn()).at(j)->getType() != 7)
                    {
                        result.push_back(getThingsFromPlayerID(getPlayerTurn()).at(j));
                        switch (getPlayerTurn()) {
                        case 1:
                            PlayerOneThing.removeAt(j);
                            break;
                        case 2:
                            PlayerTwoThing.removeAt(j);
                            break;
                        case 3:
                            PlayerThreeThing.removeAt(j);
                            break;
                        case 4:
                            PlayerFourThing.removeAt(j);
                            break;
                        default:
                            break;
                        }
                    } else {
                        j++;
                    }
                }
                emit(sendRetretThingSignal(result,getPlayerTurn()));
                //refresh the layout of the combat
                vertical_layout->addWidget(createPlayerBox(getThingsFromPlayerID(getPlayerTurn()),getPlayerTurn()),i,0);
                //check the winning
                if(!checkAllPlayerRack())
                {
                    //change to nextplayer
                    popMessageBox();
                }
                break;
            }
        }
    } else {
        //exploration lose
        Message("Sorry", "You lose the exploration");
        deleteALLWidget();
        this->close();
        emit(changeNextPlayerSingal());
    }
}

Building *Combat::getHexBuilding() const
{
    return HexBuilding;
}

void Combat::setHexBuilding(Building *value)
{
    HexBuilding = value;
}

bool Combat::checkAllPlayerRack()
{
    int count = 0;
    int remainPlayerID;
    //check for the wining of the combat
    for(int i = 0; i < playerCount.size(); i++)
    {
        if(getThingsFromPlayerID(playerCount.at(i)).size() == 0)
        {
            if(playerCount.at(i) == ownPlayer)
            {
                if(getBuildingValue() == 0)
                {
                    count++;
                }
            } else {
                count++;
            }
        } else {
            remainPlayerID = playerCount.at(i);
        }
    }
    if(isCombat)
    {
        if(count == (playerCount.size()-1))
        {
            //win the game
            Message("Congratulation", "you win the Combat");
            //close the combat
            this->close();
            //send building back to the hex
            if(getHexBuilding())
            {
                emit(sendBuildingToHexSignal(getHexBuilding(),remainPlayerID));
            }
            //send the data back to the hex
            emit(sendCombatWinnerThingSignal(getThingsFromPlayerID(remainPlayerID),remainPlayerID));        
            //refresh all the combatdata
            deleteALLWidget();
            return true;
        } else {
            return false;
        }
    } else {
        //check if the player win the exporation
        if(count == (playerCount.size()-1))
        {
            if(getThingsFromPlayerID(ownPlayer).size() != 0)
            {
                //win the exploration
                Message("Congratulation", "you win the Exploration");
                //send the data back to the hex
                emit(sendCombatWinnerThingSignal(getThingsFromPlayerID(remainPlayerID),remainPlayerID));
                //refresh all the combatdata
                deleteALLWidget();
                //close the combat
                this->close();
            } else {
                //exploration lose
                Message("Sorry", "You lose the Exploration");
                deleteALLWidget();
                this->close();
                emit(changeNextPlayerSingal());
            }
            return true;
        } else {
            return false;
        }
    }
}

void Combat::popMessageBox()
{
    QMessageBox *message = new QMessageBox(QMessageBox::NoIcon, "Combat", "Next player Turn");
    message->setIconPixmap(QPixmap(":/palyer/image/things/player_battle_building/Thing26.jpg"));
    connect(message, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(changePlayerTurnSlot(QAbstractButton*)));
    message->exec();
}

void Combat::Message(QString title, QString body)
{
    QMessageBox *message = new QMessageBox(QMessageBox::NoIcon, title, body);
    message->setIconPixmap(QPixmap(":/palyer/image/things/player_battle_building/Thing26.jpg"));
    message->exec();
    delete message;
}

void Combat::changePlayerTurnSlot(QAbstractButton* temp)
{
    //refresh the dice value
    dice->refreshLabel();

    if(getPlayerTurn() == playerCount.at(playerCount.size()-1))
    {
        //all the player finish rolling dice, begin to apply hits.vice versa
        if(rollDice)
        {
            if(getCombatTurn() <= 3)
            {
                rollDice = false;
                //start to apply hit
                dice->hide();
            } else {
                //start next combat turn
                setCombatTurn(1);
                dice->show();
                button->hide();
                button2->hide();
            }
        } else {
            rollDice = true;
            if(getCombatTurn() == 3)
            {
                setCombatTurn(getCombatTurn()+1);
                button->show();
                button2->show();
            } else {
                //start to roll dice
                dice->show();
                //start next combat turn
                setCombatTurn(getCombatTurn()+1);
            }
        }
        //change to next player
        setPlayerTurn(playerCount.at(0));
        if(getThingsFromPlayerID(getPlayerTurn()).size() == 0)
        {
            if(ownPlayer == getPlayerTurn())
            {
                if(getBuildingValue() == 0)
                {
                    //change to next player
                    changePlayerTurnSlot(temp);
                }
            } else {
                //change to next player
                changePlayerTurnSlot(temp);
            }
        }
    } else {
        //change to next player
        for(int i = 0; i < playerCount.size(); i++)
        {
            if(playerCount.at(i) == getPlayerTurn())
            {
                setPlayerTurn(playerCount.at(i+1));
                if(getThingsFromPlayerID(getPlayerTurn()).size() == 0)
                {
                    if(ownPlayer == getPlayerTurn())
                    {
                        if(getBuildingValue() == 0)
                        {
                            //change to next player
                            changePlayerTurnSlot(temp);
                        }
                    } else {
                        //change to next player
                        changePlayerTurnSlot(temp);
                    }
                }
                break;
            }
        }
    }

}

void Combat::updateDiceValueSlot(int tempDice)
{
    diceValue = tempDice;
    QList<Thing*> tempThings = getThingsFromPlayerID(getPlayerTurn());
    int addCount = 0;
    switch (getCombatTurn()) {
    case 1:
        //magic combat turn
        for(int i = 0; i < tempThings.size(); i++)
        {
            if(tempThings.at(i)->getType() == 5
                    ||tempThings.at(i)->getType() == 8
                    ||tempThings.at(i)->getType() == 9)
            {
                if(tempThings.at(i)->getAttackValue() >= diceValue)
                {
                    //increase the hipoint of this player
                    addCount++;
                }
            }
        }
        //all the buidling count
        if(getHexBuilding())
        {
            if((ownPlayer == getPlayerTurn()) && (getHexBuilding()->getID() == 4))
            {
                if(diceValue <= getBuildingValue())
                {
                    addCount++;
                }
            }
        }
        break;
    case 2:
        //ranged combat turn
        for(int i = 0; i < tempThings.size(); i++)
        {
            if(tempThings.at(i)->getType() == 4
                    ||tempThings.at(i)->getType() == 9)
            {
                if(tempThings.at(i)->getAttackValue() >= diceValue)
                {
                    //increase the hipoint of this player
                    addCount++;
                }
            }
        }
        //all the buidling count
        if(getHexBuilding())
        {
            if((ownPlayer == getPlayerTurn()) && (getHexBuilding()->getID() == 3))
            {
                if(diceValue <= getBuildingValue())
                {
                    addCount++;
                }
            }
        }
        break;
    case 3:
        //melee combat turn
        for(int i = 0; i < tempThings.size(); i++)
        {
            //normal things
            if(tempThings.at(i)->getType() == 1 ||
                    tempThings.at(i)->getType() == 2 ||
                    tempThings.at(i)->getType() == 7)
            {
                if(tempThings.at(i)->getAttackValue() >= diceValue)
                {
                    //increase the hipoint of this player
                    addCount++;
                }
            }
            //Charging creature
            if(tempThings.at(i)->getType() == 3)
            {
                if(tempThings.at(i)->getAttackValue() >= diceValue)
                {
                    addCount = addCount + 2;
                }
            }
        }
        //all the buidling count
        if(getHexBuilding())
        {
            if((ownPlayer == getPlayerTurn()) && (getHexBuilding()->getID() == 1||getHexBuilding()->getID() == 1))
            {
                if(diceValue <= getBuildingValue())
                {
                    addCount++;
                }
            }
        }
        break;
    default:
        break;
    }
    //update the hitpoint label
    for(int i = 0; i < playerCount.size(); i++)
    {
        if(playerCount.at(i) == getPlayerTurn())
        {
            //refresh the playerhitpoint label
            int hitpoint = playerHitPoint.at(i)->objectName().toInt() + addCount;
            playerHitPoint.at(i)->setObjectName(QString::number(hitpoint));
            QString temp = "Player " + QString::number(playerCount.at(i)) + " HitPoint : " + playerHitPoint.at(i)->objectName();
            playerHitPoint.at(i)->setText(temp);
        }
    }
    //change to next player
    popMessageBox();
}

void Combat::startCombatSlot(bool Combat)
{
    isCombat = Combat;
    //begin the combat
    initialLayout();
    setCombatTurn(1);
    this->show();
    checkAllPlayerRack();
}

void Combat::getBuildingFromHexSlot(Building *tempBuilding)
{
    HexBuilding = tempBuilding;
}

void Combat::getOwnPlayer(int Player)
{
    ownPlayer = Player;
}

QList<int> Combat::detectWhichPlayer()
{
    QList<int> temp;
    if(PlayerOneThing.size() != 0)
    {
        temp.push_back(1);
    }
    if(PlayerTwoThing.size() != 0)
    {
        temp.push_back(2);
    }
    if(PlayerThreeThing.size() != 0)
    {
        temp.push_back(3);
    }
    if(PlayerFourThing.size() != 0)
    {
        temp.push_back(4);
    }
    return temp;
}

void Combat::getThingFromHexSlot(QList<Thing *> tempThings, int playerID)
{
    //initial the things to the Combat widget
    switch (playerID) {
    case 1:
        PlayerOneThing = tempThings;
        break;
    case 2:
        PlayerTwoThing = tempThings;
        break;
    case 3:
        PlayerThreeThing = tempThings;
        break;
    case 4:
        PlayerFourThing = tempThings;
        break;
    default:
        break;
    }
}

QList<Thing*> Combat::getThingsFromPlayerID(int playerID)
{
    switch (playerID) {
    case 1:
        return PlayerOneThing;
        break;
    case 2:
        return PlayerTwoThing;
        break;
    case 3:
        return PlayerThreeThing;
        break;
    case 4:
        return PlayerFourThing;
        break;
    default:
        break;
    }
}
