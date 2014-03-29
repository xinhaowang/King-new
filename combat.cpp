#include "combat.h"
#include "ui_combat.h"

Combat::Combat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Combat)
{
    ui->setupUi(this);
    this->setObjectName("Combat");
}

Combat::~Combat()
{
    delete ui;
}

QGroupBox *Combat::createPlayerBox(QList<Thing*> tempThings)
{
    QGroupBox *groupBox = new QGroupBox(tr("Player  Things"));
    QGridLayout *vbox = new QGridLayout();
    QList<QPushButton*> tempButton;
    for(int i = 0; i < tempThings.size(); i++)
    {
        QPushButton *button = new QPushButton;
        button->setObjectName(QString::number(tempThings.at(i)->getID()));
        QString temp = "border-image: url(" + tempThings.at(i)->getUrl();
        button->setStyleSheet(temp + ")");
        button->setFixedSize(80,80);
        tempButton.push_back(button);
    }
    for(int i = 0; i < tempButton.size(); i++)
    {
        if(i < 5)
        {
            vbox->addWidget(tempButton.at(i),0,i);
        } else {
            vbox->addWidget(tempButton.at(i),1,i);
        }
    }
    groupBox->setLayout(vbox);
    return groupBox;
}

void Combat::initialLayout()
{
    QGridLayout *vertical_layout = new QGridLayout;
    QList<int> playerCount = detectWhichPlayer();
    for(int i = 0; i < playerCount.size(); i++)
    {
        switch (playerCount.at(i)) {
        case 1:
            vertical_layout->addWidget(createPlayerBox(PlayerOneThing),i,0);
            break;
        case 2:
            vertical_layout->addWidget(createPlayerBox(PlayerTwoThing),i,0);
            break;
        case 3:
            vertical_layout->addWidget(createPlayerBox(PlayerThreeThing),i,0);
            break;
        case 4:
            vertical_layout->addWidget(createPlayerBox(PlayerFourThing),i,0);
            break;
        default:
            break;
        }
    }
    QWidget *widget = new QWidget(this);
    widget->setLayout(vertical_layout);
    widget->resize(900,900);
}

void Combat::startCombatSlot()
{
    //begin the combat
    initialLayout();
}

void Combat::startExplorationSlot()
{
    //begin the exploration
    initialLayout();
}

void Combat::initQGroupBox()
{

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

