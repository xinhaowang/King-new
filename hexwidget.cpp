#include "hexwidget.h"

HexWidget::HexWidget(QWidget *parent) :
    QWidget(parent)
{
}

HexWidget::HexWidget(QWidget *parent, Hex *tempHex) :
    QWidget(parent), m_hexData(tempHex), m_building(NULL), m_heroLabel(NULL)
{
    this->setAcceptDrops(false);
    this->setIsEnabledClick(false);
    this->setIsEnableDrag(false);
    this->setSelectState(3);
    battle = false;
}

/********************************************************************
 *
 * public
 *
 * ******************************************************************/
void HexWidget::refreshMyLabel()
{
    QList<mylabel*> tempLabel;
    for(int i = 0; i < m_thingsLabel.size(); i++)
    {
        if(m_thingsLabel.at(i)->pos() == QPoint(0,0))
        {
            tempLabel.push_back(m_thingsLabel.at(i));
        }
    }
    //draw the label
    for(int i = 0; i < tempLabel.size(); i++)
    {
        switch (playerID) {
        case 1:
            tempLabel[i]->setGeometry(15,5,30,30);
            tempLabel[i]->show();
            break;
        case 2:
            tempLabel[i]->setGeometry(65,5,30,30);
            tempLabel[i]->show();
            break;
        case 3:
            tempLabel[i]->setGeometry(15,65,30,30);
            tempLabel[i]->show();
            break;
        case 4:
            tempLabel[i]->setGeometry(65,65,30,30);
            tempLabel[i]->show();
            break;
        default:
            break;
        }
    }
    this->repaint();
}

HeroLabel *HexWidget::heroLabel() const
{
    return m_heroLabel;
}

void HexWidget::setHeroLabel(HeroLabel *heroLabel)
{
    m_heroLabel = heroLabel;

}

Hex *HexWidget::hexData() const
{
    return m_hexData;
}

void HexWidget::setHexData(Hex *hexData)
{
    m_hexData = hexData;
}

int HexWidget::getID() const
{
    return ID;
}

void HexWidget::setID(int value)
{
    ID = value;
}

bool HexWidget::getIsEnableDrag() const
{
    return isEnableDrag;
}

void HexWidget::setIsEnableDrag(bool value)
{
    emit(requirePlayerIDnPhaseSignal());
    if(value)
    {
        setSelectState(1);
        this->setAcceptDrops(true);
    } else {
        setSelectState(0);
        this->setAcceptDrops(false);
    }
    isEnableDrag = value;
}

bool HexWidget::getIsEnabledClick() const
{
    return isEnabledClick;
}

void HexWidget::setIsEnabledClick(bool value)
{
    emit(requirePlayerIDnPhaseSignal());
    if(value)
    {
        setSelectState(1);
    } else {
        setSelectState(0);
    }
    isEnabledClick = value;
}

//0 for normal, 1 for green(can use), 2 for red(selected)
int HexWidget::getSelectState() const
{
    return SelectState;
}

void HexWidget::setSelectState(int value)
{
    SelectState = value;
    this->update();
}

Building *HexWidget::building() const
{
    return m_building;
}

void HexWidget::setBuilding(Building *building)
{
    m_building = building;
}

void HexWidget::deleteBuilding()
{
    m_building = NULL;
}

QList<mylabel *> HexWidget::thingsLabel() const
{
    return m_thingsLabel;
}

QList<mylabel *> HexWidget::getPlayerThingsLabel(int playerID)
{
    QList<mylabel *> temp;
    switch (playerID) {
    case 1:
        for(int i = 0; i < m_thingsLabel.size(); i++)
        {
            if(m_thingsLabel.at(i)->geometry().contains(30,15))
            {
                temp.push_back(m_thingsLabel.at(i));
            }
        }
        break;
    case 2:
        for(int i = 0; i < m_thingsLabel.size(); i++)
        {
            if(m_thingsLabel.at(i)->geometry().contains(65,15))
            {
                temp.push_back(m_thingsLabel.at(i));
            }
        }
        break;
    case 3:
        for(int i = 0; i < m_thingsLabel.size(); i++)
        {
            if(m_thingsLabel.at(i)->geometry().contains(25,65))
            {
                temp.push_back(m_thingsLabel.at(i));
            }
        }
        break;
    case 4:
        for(int i = 0; i < m_thingsLabel.size(); i++)
        {
            if(m_thingsLabel.at(i)->geometry().contains(65,65))
            {
                temp.push_back(m_thingsLabel.at(i));
            }
        }
        break;
    default:
        break;
    }
    return temp;
}

void HexWidget::setThingsLabel(mylabel* thingsLabel)
{
    m_thingsLabel.push_back(thingsLabel);
    refreshMyLabel();
}

void HexWidget::deleteThingsLabel(QList<mylabel *> tempthingsLabel)
{
    for(int i = 0; i < tempthingsLabel.size(); i++)
    {
        for(QList<mylabel *>::iterator iter = m_thingsLabel.begin();
            iter != m_thingsLabel.end();)
        {
            if(tempthingsLabel.at(i)->getData()->getID() == (*iter)->getData()->getID())
            {
                delete *iter;
                iter = m_thingsLabel.erase(iter);
            } else {
                iter++;
            }
        }
    }
}

void HexWidget::deleteAllThingsLabel()
{
    qDeleteAll(m_thingsLabel);
    m_thingsLabel.clear();
}

void HexWidget::returnAllThings()
{
    for(int i = 0; i < m_thingsLabel.size(); i++)
    {
        m_thingsLabel.at(i)->getData()->setInRack(true);
        m_thingsLabel.at(i)->getData()->setUsed(false);       
    }
    qDeleteAll(m_thingsLabel);
    m_thingsLabel.clear();
}
/********************************************************************
 *
 * protected
 *
 * ******************************************************************/
void HexWidget::mousePressEvent(QMouseEvent *event)
{
    emit(requirePlayerIDnPhaseSignal());
    if(Qt::LeftButton == event->button())
    {
        //if this hex not been owned, set up the board
        if(this->objectName() == "0" && phase == 0 && isEnabledClick)
        {
            //show that this hex has been owned
            this->setObjectName("1");
            this->setSelectState(0);
            this->setIsEnabledClick(false);
            emit(hexHasChangedSignal(this));
        } else if (this->objectName() == "1" && isEnabledClick && phase == 0) {
            //set up the building for this hex
            //emit the signal to the mainwindow
            emit(setBulidngSingal(this));
        } else if (isEnabledClick && phase == 2) {
            emit(setHeroSignal(this));
        } else if (isEnabledClick && phase == 5) {
            //movement phase
            emit(setThingsToMoveWidgetSignal(this));
        } else if (isEnabledClick && phase == 6) {
            //combat pahse
            emit(startCombatSignal(this));
        }
    }
}

void HexWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QString temp;
    switch (SelectState) {
    case 0:
        //do nothing about the stylesheet
        temp = "border-image: url(" +  m_hexData->getUrl() + ");";
        this->setStyleSheet(temp);
        break;
    case 1:
        //add the greeen frame
        temp = "border-image: url(" +  m_hexData->getGreenUrl() + ");";
        this->setStyleSheet(temp);
        break;
    case 2:
        //add the red frame
        temp = "border-image: url(" +  m_hexData->getRedUrl() + ");";
        this->setStyleSheet(temp);
        break;
    case 3:
        this->setStyleSheet("border-image: url(:/background/image/background/white.jpg)");
        break;
    case 4:
        this->setStyleSheet("border-image: url(:/background/image/background/dice1.gif)");
    default:
        break;
    }
    QWidget::paintEvent(e);
}

void HexWidget::dragEnterEvent(QDragEnterEvent *event)
{
    const ThingMimeData *tempMimeData = (const ThingMimeData*)event->mimeData();
    const QList<Thing*>* tempList = tempMimeData->thingDragData();
    if(tempList)
    {
        event->accept();
    }
}

void HexWidget::dropEvent(QDropEvent *event)
{
    emit(requirePlayerIDnPhaseSignal());
    const ThingMimeData *pMimeData = (const ThingMimeData*)event->mimeData();
    const QList<Thing*>* tempList = pMimeData->thingDragData();
    QList<Thing*> pList;
    //check the things can move or not
    if(phase == 5)
    {
        if(m_hexData->getTypeID() == 8||
                m_hexData->getTypeID() == 6||
                m_hexData->getTypeID() == 3||
                m_hexData->getTypeID() == 5)
        {
            for(int i = 0; i < tempList->size(); i++)
            {
                if(tempList->at(i)->getMovementCount() == 0||
                        tempList->at(i)->getMovementCount() == 1)
                {
                    //things can't move, because there is not enough movment count
                    Message("Warning", "Don't have enough movment count");
                    emit(sendbackOneThingSignal(tempList->at(i)));
                } else {
                    pList.push_back(tempList->at(i));
                }
            }
        } else {
            for(int i = 0; i < tempList->size(); i++)
            {
                if(tempList->at(i)->getMovementCount() == 0)
                {
                    //things can't move, because there is not enough movment count
                    Message("Warning", "Don't have enough movment count");
                    emit(sendbackOneThingSignal(tempList->at(i)));
                } else {
                    pList.push_back(tempList->at(i));
                }
            }
        }
        //check the total things should be no more than 10
        if(getPlayerThingsLabel(playerID).size() + pList.size() > 10)
        {
            Message("Warning", "Too many things");
            emit(sendThingsBackToHex(pList));

        } else if(m_hexData->getTypeID() == 1){
            //hex is sea
            //check if the things contain flying feature
            Message("Warning", "Only flying feature can pass sea");
            for(int i = 0; i < pList.size(); i++)
            {
                //things is flying feature
                if(pList.at(i)->getType() == 2)
                {
                    pList.at(i)->setMovementCount(pList.at(i)->getMovementCount() - 1);
                    pList.at(i)->setMode(SmallIcon_Mode);
                    pList.at(i)->setInRack(false);
                    mylabel *tempLabel = new mylabel(pList.at(i), this);
                    m_thingsLabel.push_back(tempLabel);
                } else {
                    //they are not flying feature
                    emit(sendbackOneThingSignal(pList.at(i)));
                }
            }
        } else {
            if(pList.size() != 0)
            {

                for(int i = 0; i < pList.size(); i++)
                {
                    if(m_hexData->getTypeID() == 8||
                            m_hexData->getTypeID() == 6||
                            m_hexData->getTypeID() == 3||
                            m_hexData->getTypeID() == 5)
                    {
                        if(pList.at(i)->getType() == 2 || pList.at(i)->getType() == 8)
                        {
                            pList.at(i)->setMovementCount(pList.at(i)->getMovementCount() - 1);
                        } else {
                            pList.at(i)->setMovementCount(pList.at(i)->getMovementCount() - 2);
                        }
                    } else {
                        pList.at(i)->setMovementCount(pList.at(i)->getMovementCount() - 1);
                    }
                    pList.at(i)->setMode(SmallIcon_Mode);
                    pList.at(i)->setInRack(false);
                    mylabel *tempLabel = new mylabel(pList.at(i), this);
                    m_thingsLabel.push_back(tempLabel);
                }
                event->accept();
            }
        }
        emit(refreshMapClickState(this));
    } else {
        if(tempList)
        {
            for(int i = 0; i < tempList->size(); i++)
            {
                //check if the hex have hero or special income
                bool checkHeroSpecial = false;
                for(int j = 0; j < m_thingsLabel.size(); j++)
                {
                    if(m_thingsLabel.at(j)->getData()->getType() == 7)
                    {
                        checkHeroSpecial = true;
                    }
                }
                if(m_heroLabel)
                {
                    checkHeroSpecial = true;
                }
                if(tempList->at(i)->getType() == 7 && checkHeroSpecial)
                {
                    Message("Warning", "Already have hero or special income");
                    emit(sendbackThingSignal(tempList->at(i)));
                    continue;
                } else if(m_thingsLabel.size() >= 10) {
                    Message("Warning","Too many things");
                    for(int j = i; j < tempList->size(); j++)
                    {
                        emit(sendbackThingSignal(tempList->at(j)));
                    }
                    break;
                } else if(tempList->at(i)->getType() == 6 ||
                          tempList->at(i)->getType() == 10 ||
                          tempList->at(i)->getType() == 11){
                    Message("Warning", "Things are treasure or magic or event, can't move");
                    emit(sendbackThingSignal(tempList->at(i)));
                    continue;
                } else {
                    tempList->at(i)->setMode(SmallIcon_Mode);
                    tempList->at(i)->setInRack(false);
                    mylabel *tempLabel = new mylabel(tempList->at(i), this);
                    m_thingsLabel.push_back(tempLabel);
                    emit(refrshThingRack());
                }
            }
            event->accept();
        }
    }
    pList.clear();
    refreshMyLabel();
}

void HexWidget::Message(QString title, QString body)
{
    QMessageBox *message = new QMessageBox(QMessageBox::NoIcon, title, body);
    message->setIconPixmap(QPixmap(":/palyer/image/things/player_battle_building/Thing26.jpg"));
    message->exec();
}
/********************************************************************
 *
 * public slots
 *
 * ******************************************************************/
void HexWidget::setPlayerIDnPhaseSlot(int tempPlayerID, int tempPhase)
{
    playerID = tempPlayerID;
    phase = tempPhase;
}
bool HexWidget::getBattle() const
{
    return battle;
}

void HexWidget::setBattle(bool value)
{
    battle = value;
}



















