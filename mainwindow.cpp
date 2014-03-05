#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initial the game board
    ui->setupUi(this);
    setBackground();
    this->setWindowTitle("King and Thing");
    setThingsRack();

    //set up the game
    setPlayerTurn(1);
    setPhaseTurn(0);
    initData();
    initMap();


    //send data to the player's rack(test)
    connect(this, SIGNAL(initThingToRackSignal(vector<Thing*>)),
            Things_rack, SLOT(initThingToRackSlot(vector<Thing*>)));
    //send player1's things to the rack
    emit(initThingToRackSignal(GameData->getPlayerFromID(1)->getInRackThings()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * general function for mainwindow
 * */
//get the random number from 1 to range
int MainWindow::getRandomNumber(int range)
{
    int x = rand() % range + 1;
    return x;
}

//set the background of the main window
void MainWindow::setBackground()
{
    ui->centralWidget->setObjectName("mypage");
    ui->centralWidget->setStyleSheet("QWidget#mypage{border-image: url(:/background/image/background/background.jpg)}");
}

//set up the Things Rack Widget
void MainWindow::setThingsRack()
{
    Things_rack = new MapWidget(this);
    Things_rack->setFixedSize(500, 240);
    Things_rack->move(700, 520);
}

//initial all the Data
void MainWindow::initData()
{
    GameData = new Control(this);
    GameData->initThings();
    GameData->initPlayers();
    GameData->initHex();
}

//initial all the Hex in the map
void MainWindow::initMap()
{
    for(size_t i = 0; i < 37; i++)
    {
        HexWidget *tempHexWidget = new HexWidget(this->centralWidget(),
                                                 GameData->hex()[(getRandomNumber(8) - 1)]);
        connect(tempHexWidget, SIGNAL(hexHasChangedSignal(HexWidget*)), this, SLOT(hexHasChangedSlot(HexWidget*)));
        connect(tempHexWidget, SIGNAL(requirePlayerIDSignal()), this, SLOT(getRequirePlayerIDSlot()));
        connect(this, SIGNAL(sendPlayerIDSignal(int)), tempHexWidget, SLOT(setPlayerIDSlot(int)));
        //show that this widget is unowned
        tempHexWidget->setObjectName("0");
        tempHexWidget->setGeometry(getMapRect(i));        
        tempHexWidget->setStyleSheet("");
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

//hex own has changed
void MainWindow::hexHasChangedSlot(HexWidget *tempHexWidget)
{
    int playerID = getPlayerTurn();
    GameData->addHexWidget(tempHexWidget, playerID);
}

void MainWindow::getRequirePlayerIDSlot()
{
    emit(sendPlayerIDSignal(getPlayerTurn()));
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

}




