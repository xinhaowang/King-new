#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initial the all the widget and background
    ui->setupUi(this);
    setBackground();
    this->setWindowTitle("King and Thing");
    setThingsRack();

    //game start, set player turn and initial the board
    initData();
    initMap();
    //start to play
    setPlayerTurn(1);
    setPhaseTurn(0);

    //send data to the player's rack
    connect(this, SIGNAL(initThingToRackSignal(vector<Thing*>)),
            Things_rack, SLOT(initThingToRackSlot(vector<Thing*>)));
    connect(Things_rack, SIGNAL(startDragSignal()),
            this, SLOT(startDragSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*********************************************************
 *
 * function for the phase 0
 *
 * *******************************************************/
//Each player set up the board in phase 0
//there are four hex that the first player can choose
void MainWindow::startInitMap()
{
    m_hexWidget[4]->setIsEnabledClick(true);
    m_hexWidget[8]->setIsEnabledClick(true);
    m_hexWidget[31]->setIsEnabledClick(true);
    m_hexWidget[35]->setIsEnabledClick(true);
}

void MainWindow::hexHasChangedSlot(HexWidget *tempHexWidget)
{
    int playerID = getPlayerTurn();
    GameData->addHexWidget(tempHexWidget, playerID);
    //set the control mark on this Hex
    QImage tempImage = QImage(GameData->getPlayerFromID(playerID)->getControlMark());
    QPixmap pixmap = QPixmap::fromImage(tempImage.scaled(QSize(30,30), Qt::IgnoreAspectRatio));
    QLabel *controlMark = new QLabel(tempHexWidget);
    controlMark->setFixedSize(30,30);
    controlMark->setGeometry(42,35,30,30);
    controlMark->setPixmap(pixmap);
    controlMark->show();
    //enable the nearby Hex
    int tempHexID = tempHexWidget->getID();
    QList<int> temp = getNearHex(tempHexID);
    for(size_t i = 0; i < temp.size(); i++)
    {
        m_hexWidget[temp.at(i)]->setIsEnabledClick(true);
    }
    //show the warning message
    //and call the next player
    popMessageBox(1);
    tempHexWidget->setSelectState(0);
    //check for next step
    int count = 0;
    for(int i = 1; i < 5; i++)
    {
        if(GameData->getPlayerFromID(i)->getPlayerHexs().size() == 3)
        {
            count++;
        }
    }
    //if all the player set up their three hex
    //set up the gold and one tower
    if(count == 4)
    {
        //init the gold and tower
        this->initGlodnTower();
    }
}

void MainWindow::initGlodnTower()
{
    this->disableMapClick();
    int playerID = getPlayerTurn();
    //set up the gold
    GameData->getPlayerFromID(playerID)->setGold(10);
    //set up the building to the player
    GameData->getPlayerFromID(playerID)->setPlayerBuilding(GameData->getBuildingFromID(1));
    //set the tower
    button = new QPushButton(this);
    button->setGeometry(900,250,80,80);
    connect(button,SIGNAL(clicked()),this,SLOT(buttonSlot()));
    QString tempBuidlingUrl = GameData->getPlayerFromID(playerID)->getPlayerBuildings().at(0)->getUrl();
    QString temp = "border-image: url(" +  tempBuidlingUrl + ");";
    button->setStyleSheet(temp);
    button->show();
}

void MainWindow::initThing()
{
    //collect things
    button->setText("Collect");
    connect(button,SIGNAL(clicked()),this,SLOT(initThingSlot()));
    button->show();
}

void MainWindow::initThingSlot()
{
    vector<Thing *> temp = GameData->getRandomThingFromNum(10);
    //set the thing to the player
    GameData->getPlayerFromID(getPlayerTurn())->setPlayerThings(temp);
    emit(initThingToRackSignal(GameData->getPlayerFromID(getPlayerTurn())->getPlayerThings()));
    disconnect(button,SIGNAL(clicked()),this,SLOT(initThingSlot()));
    button->setText("Next");
    connect(button,SIGNAL(clicked()),this,SLOT(confirmThingSlot()));
}

void MainWindow::confirmThingSlot()
{
    button->hide();
    disconnect(button,SIGNAL(clicked()),this,SLOT(confirmThingSlot()));
    //change next player
    popMessageBox(1);
    disableMapClick();
    Things_rack->hide();

    int count = 0;
    for(size_t i = 0; i < 4; i++)
    {
        if(GameData->getPlayerFromID(i+1)->getPlayerThings().size() != 0)
        {
            count++;
        }
    }
    if(count == 4)
    {
        //go to another phase
    } else {
        initThing();
    }
}

void MainWindow::startDragSlot()
{
    vector<HexWidget *> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(size_t i = 0; i < temp.size(); i++)
    {
        temp.at(i)->setIsEnableDrag(true);
    }
}

void MainWindow::buttonSlot()
{
    vector<HexWidget*> temp = GameData->getPlayerFromID(getPlayerTurn())->getPlayerHexs();
    for(size_t i = 0; i < temp.size(); i++)
    {
        temp[i]->setIsEnabledClick(true);
    }
}

void MainWindow::setBuildingToHexSlot(HexWidget *tempHexWidget)
{
    //draw the buildings on the Hex
    QString tempBuidlingUrl = GameData->getPlayerFromID(getPlayerTurn())->getPlayerBuildings().at(0)->getUrl();
    QImage tempImage = QImage(tempBuidlingUrl);
    QPixmap pixmap = QPixmap::fromImage(tempImage.scaled(QSize(30,30), Qt::IgnoreAspectRatio));
    QLabel *building = new QLabel(tempHexWidget);
    building->setFixedSize(30,30);
    building->setGeometry(72,35,30,30);
    building->setPixmap(pixmap);
    building->show();
    //pass the building to the hex
    tempHexWidget->setBuilding(GameData->getPlayerFromID(getPlayerTurn())->getPlayerBuildings().at(0));
    //disable the click for hex
    disableMapClick();
    //delete the button of the mainwindow
    disconnect(button,SIGNAL(clicked()),this,SLOT(buttonSlot()));
    button->setStyleSheet("");
    button->hide();
    //change next player
    popMessageBox(2);
}

//popup message box change next player
void MainWindow::popMessageBox(int index)
{
    QMessageBox *message = new QMessageBox(QMessageBox::NoIcon, "Next Player", "Next player Turn");
    message->setIconPixmap(QPixmap(":/palyer/image/things/player_battle_building/Thing26.jpg"));
    switch (index) {
    case 1:
        connect(message, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(changePlayerTurnSlot(QAbstractButton*)));
        break;
    case 2:
        connect(message, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(changePlayerTurnSlot2(QAbstractButton*)));
        break;
    default:
        break;
    }
    message->exec();
}

void MainWindow::changePlayerTurnSlot(QAbstractButton*)
{
    setPlayerTurn(getPlayerTurn()%4 + 1);
}

void MainWindow::changePlayerTurnSlot2(QAbstractButton *)
{
    setPlayerTurn(getPlayerTurn()%4 + 1);
    //if every one set the tower then system divide things
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        if(GameData->getPlayerFromID(i+1)->getPlayerBuildings().size() == 1)
        {
            count++;
        }
    }
    if(count == 4)
    {
        //go to the next step
        initThing();
    } else {
        this->initGlodnTower();
    }
}

/*********************************************************
 *
 * general function
 *
 * *******************************************************/

//index should between 0-36
QList<int> MainWindow::getNearHex(int index)
{
    QList<int> temp;
    switch (index) {
    case 0:
        temp << 1 << 2 << 3;
        break;
    case 4:
        temp << 1 << 5 << 9 << 10;
        break;
    case 8:
        temp << 3 << 7 << 14 << 15;
        break;
    case 31:
        temp << 30 << 24 << 25 << 32;
        break;
    case 35:
        temp << 34 << 28 << 27 << 36;
        break;
    default:
        break;
    }
    return temp;
}

int MainWindow::getPlayerTurn() const
{
    return playerTurn;
}

void MainWindow::setPlayerTurn(int value)
{
    playerTurn = value;
    QString temp = "Player : " + QString::number(value) + " turn.";
    ui->label->setText(temp);
    ui->label->setStyleSheet("background-color: white;");
}

int MainWindow::getPhaseTurn() const
{
    return PhaseTurn;
}

void MainWindow::setPhaseTurn(int value)
{
    PhaseTurn = value;
    QString temp = "Phase : " + QString::number(value) + ".";
    ui->label_2->setText(temp);
    ui->label_2->setStyleSheet("background-color: white;");
    switch (value) {
    case 0:
        startInitMap();
        break;
    default:
        break;
    }
}

void MainWindow::disableMapClick()
{
    for(size_t i = 0; i < m_hexWidget.size(); i++)
    {
        m_hexWidget[i]->setIsEnabledClick(false);
    }
}

void MainWindow::getRequirePlayerIDnPhaseSlot()
{
    emit(sendPlayerIDnPhaseSignal(getPlayerTurn(), getPhaseTurn()));
}

//get the random number from 1 to range
int MainWindow::getRandomNumber(int range)
{
    int x = rand() % range + 1;
    return x;
}

/*********************************************************
 *
 * initial function
 *
 * *******************************************************/
//set the background of the main window
void MainWindow::setBackground()
{
    ui->centralWidget->setObjectName("mypage");
    ui->centralWidget->setStyleSheet("QWidget#mypage{border-image: url(:/background/image/background/background.jpg)}");
}
//initial all the Data
void MainWindow::initData()
{
    GameData = new Control(this);
    GameData->initThings();
    GameData->initPlayers();
    GameData->initHex();
    GameData->initBuilding();
}
//initial all the Hex in the map
void MainWindow::initMap()
{
    for(size_t i = 0; i < 37; i++)
    {
        HexWidget *tempHexWidget = new HexWidget(this->centralWidget(),
                                                 GameData->hex()[(getRandomNumber(8) - 1)]);
        connect(tempHexWidget, SIGNAL(hexHasChangedSignal(HexWidget*)),
                this, SLOT(hexHasChangedSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(requirePlayerIDnPhaseSignal()),
                this, SLOT(getRequirePlayerIDnPhaseSlot()));
        connect(this, SIGNAL(sendPlayerIDnPhaseSignal(int, int)),
                tempHexWidget, SLOT(setPlayerIDnPhaseSlot(int, int)));
        connect(tempHexWidget, SIGNAL(setBulidngSingal(HexWidget*)),
                this, SLOT(setBuildingToHexSlot(HexWidget*)));
        //show that this widget is unowned
        tempHexWidget->setObjectName("0");
        tempHexWidget->setID(i);
        tempHexWidget->setGeometry(getMapRect(i));
        m_hexWidget.push_back(tempHexWidget);
    }
}
QRect MainWindow::getMapRect(int index)
{
    int HexWidth = 114;
    int HexHeight = 100;
    switch (index) {
    case 0:
        return QRect(290,30,HexWidth,HexHeight);
        break;
    case 1:
        return QRect(200,80,HexWidth,HexHeight);
        break;
    case 2:
        return QRect(290,130,HexWidth,HexHeight);
        break;
    case 3:
        return QRect(380,80,HexWidth,HexHeight);
        break;
    case 4:
        return QRect(110,130,HexWidth,HexHeight);
        break;
    case 5:
        return QRect(200,180,HexWidth,HexHeight);
        break;
    case 6:
        return QRect(290,230,HexWidth,HexHeight);
        break;
    case 7:
        return QRect(380,180,HexWidth,HexHeight);
        break;
    case 8:
        return QRect(470,130,HexWidth,HexHeight);
        break;
    case 9:
        return QRect(20,180,HexWidth,HexHeight);
        break;
    case 10:
        return QRect(110,230,HexWidth,HexHeight);
        break;
    case 11:
        return QRect(200,280,HexWidth,HexHeight);
        break;
    case 12:
        return QRect(290,330,HexWidth,HexHeight);
        break;
    case 13:
        return QRect(380,280,HexWidth,HexHeight);
        break;
    case 14:
        return QRect(470,230,HexWidth,HexHeight);
        break;
    case 15:
        return QRect(560,180,HexWidth,HexHeight);
        break;
    case 16:
        return QRect(20,280,HexWidth,HexHeight);
        break;
    case 17:
        return QRect(110,330,HexWidth,HexHeight);
        break;
    case 18:
        return QRect(200,380,HexWidth,HexHeight);
        break;
    case 19:
        return QRect(290,430,HexWidth,HexHeight);
        break;
    case 20:
        return QRect(380,380,HexWidth,HexHeight);
        break;
    case 21:
        return QRect(470,330,HexWidth,HexHeight);
        break;
    case 22:
        return QRect(560,280,HexWidth,HexHeight);
        break;
    case 23:
        return QRect(20,380,HexWidth,HexHeight);
        break;
    case 24:
        return QRect(110,430,HexWidth,HexHeight);
        break;
    case 25:
        return QRect(200,480,HexWidth,HexHeight);
        break;
    case 26:
        return QRect(290,530,HexWidth,HexHeight);
        break;
    case 27:
        return QRect(380,480,HexWidth,HexHeight);
        break;
    case 28:
        return QRect(470,430,HexWidth,HexHeight);
        break;
    case 29:
        return QRect(560,380,HexWidth,HexHeight);
        break;
    case 30:
        return QRect(20,480,HexWidth,HexHeight);
        break;
    case 31:
        return QRect(110,530,HexWidth,HexHeight);
        break;
    case 32:
        return QRect(200,580,HexWidth,HexHeight);
        break;
    case 33:
        return QRect(290,630,HexWidth,HexHeight);
        break;
    case 34:
        return QRect(380,580,HexWidth,HexHeight);
        break;
    case 35:
        return QRect(470,530,HexWidth,HexHeight);
        break;
    case 36:
        return QRect(560,480,HexWidth,HexHeight);
        break;
    default:
        return QRect();
        break;
    }

}
//set up the Things Rack Widget
void MainWindow::setThingsRack()
{
    Things_rack = new MapWidget(this);
    Things_rack->setFixedSize(500, 240);
    Things_rack->move(700, 520);
}





