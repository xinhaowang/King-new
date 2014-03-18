#include "hexwidget.h"

HexWidget::HexWidget(QWidget *parent) :
    QWidget(parent)
{
}

HexWidget::HexWidget(QWidget *parent, Hex *tempHex) :
    QWidget(parent), m_hexData(tempHex), m_building(NULL), m_heroLabel(NULL)
{
    this->setStyleSheet("border-image: url(:/background/image/background/white.jpg)");
    oldStyle = this->styleSheet();
    this->setAcceptDrops(false);
    this->setIsEnabledClick(false);
    this->setIsEnableDrag(false);
    this->setSelectState(0);
}

/********************************************************************
 *
 * public
 *
 * ******************************************************************/
void HexWidget::refreshMyLabel()
{
    //draw the label
    for(size_t i = 0; i < m_thingsLabel.size(); i++)
    {
        switch (playerID) {
        case 1:
            m_thingsLabel[i]->setGeometry(20,10,80,80);
            m_thingsLabel[i]->show();
            break;
        case 2:
            m_thingsLabel[i]->setGeometry(60,10,80,80);
            m_thingsLabel[i]->show();
            break;
        case 3:
            m_thingsLabel[i]->setGeometry(20,60,80,80);
            m_thingsLabel[i]->show();
            break;
        case 4:
            m_thingsLabel[i]->setGeometry(60,60,80,80);
            m_thingsLabel[i]->show();
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

vector<mylabel *> HexWidget::thingsLabel() const
{
    return m_thingsLabel;
}

void HexWidget::setThingsLabel(const vector<mylabel *> &thingsLabel)
{
    m_thingsLabel = thingsLabel;
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
            QString temp = "border-image: url(" +  m_hexData->getUrl() + ");";
            this->setStyleSheet(temp);
            oldStyle = this->styleSheet();
            this->setSelectState(2);
            this->setIsEnabledClick(false);
            emit(hexHasChangedSignal(this));
        } else if (this->objectName() == "1" && isEnabledClick && phase == 0) {
            //set up the building for this hex
            //emit the signal to the mainwindow
            emit(setBulidngSingal(this));
        } else if (isEnabledClick && phase == 2) {
            emit(setHeroSignal(this));
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
        this->setStyleSheet(oldStyle);
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
    const QList<Thing*>* pList = pMimeData->thingDragData();
    if(pList)
    {
        for(int i = 0; i < pList->size(); i++)
        {
            pList->at(i)->setMode(SmallIcon_Mode);
            mylabel *tempLabel = new mylabel(pList->at(i), this);
            m_thingsLabel.push_back(tempLabel);
        }
        event->accept();
    }
    refreshMyLabel();
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


















