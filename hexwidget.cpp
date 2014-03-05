#include "hexwidget.h"

HexWidget::HexWidget(QWidget *parent) :
    QWidget(parent)
{
}

HexWidget::HexWidget(QWidget *parent, Hex *tempHex) :
    QWidget(parent), m_hexData(tempHex)
{
    this->setAcceptDrops(false);
}


void HexWidget::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        //if this hex not been owned
        if(this->objectName() == "0")
        {
            //show that this hex has been owned
            this->setObjectName("1");
            emit(hexHasChangedSignal(this));
            QString temp = "border-image: url(" +  m_hexData->getUrl() + ");";
            this->setStyleSheet(temp);
            this->setAcceptDrops(true);
        } else if (this->objectName() == "1") {

        }
    }
}

void HexWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}

void HexWidget::setPlayerIDSlot(int tempPlayerID)
{
    playerID = tempPlayerID;
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

void HexWidget::refreshMyLabel()
{
    emit(requirePlayerIDSignal());
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





