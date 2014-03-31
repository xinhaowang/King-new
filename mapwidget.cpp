#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAcceptDrops(true);
}

MapWidget::~MapWidget()
{

}

void MapWidget::initThingToRackSlot(QList<Thing*> tempThings)
{
    clear();
    for(int i = 0; i < tempThings.size(); i++)
    {
        tempThings.at(i)->setMode(BigIcon_Mode);
        mylabel *tempThingLabel = new mylabel(tempThings[i], this);
        m_thingsLabel.push_back(tempThingLabel);
    }
    for(int i = 0; i < m_thingsLabel.size(); i++)
    {
        QRect rect = getThingRect(i);
        if(i == m_thingsLabel.size() - 1)
        {
            this->setMinimumHeight(rect.y() + 80);
        }
        m_thingsLabel[i]->setGeometry(rect);
        m_thingsLabel[i]->show();
    }
}

QRect MapWidget::getThingRect(int index)
{
    if(index < 0 || index > m_thingsLabel.size())
    {
        return QRect();
    }
    const int spacing = 10;
    int width = this->width();
    int itemWidth = m_thingsLabel[index]->width();
    int itemHeight = m_thingsLabel[index]->height();
    int colCount = width/(itemWidth + spacing);
    int row = index/colCount;
    int col = index%colCount;
    int xPosn = col*(itemWidth + spacing);
    int yPosn = row*(itemHeight + spacing);
    return QRect(xPosn, yPosn, itemWidth, itemHeight);
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    m_mousePressPosn = event->pos();
    //clear all the select things if we press right button
    if(Qt::RightButton == event->button())
    {
        for(int i = 0; i < m_selectThingsLabel.size(); i++)
        {
            m_selectThingsLabel[i]->unSelectedThing();
        }
        m_selectThingsLabel.clear();
    } else if (Qt::LeftButton == event->button()) {
        for(int i = 0; i < m_thingsLabel.size(); i++)
        {
            QRect rect = getThingRect(i);
            if(rect.contains(m_mousePressPosn))
            {
                if(m_thingsLabel[i]->selected())
                {
                    unSelectThing();
                } else {
                    selectThing();
                }
            }
        }
        update();
    } else if (Qt::MidButton == event->button() && (m_selectThingsLabel.size() > 0)) {
        performDrag();
    }
    QWidget::mousePressEvent(event);
}

void MapWidget::reLayoutIconSlot()
{
    for(int i = 0; i < m_thingsLabel.size(); i++)
    {
        QRect rect = getThingRect(i);
        m_thingsLabel[i]->setGeometry(rect);
        m_thingsLabel[i]->show();
    }
    this->repaint();
}

void MapWidget::clear()
{
    qDeleteAll(m_thingsLabel);
    m_thingsLabel.clear();
    m_selectThingsLabel.clear();
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePosn = event->pos();
    QWidget::mouseMoveEvent(event);
}

void MapWidget::dragEnterEvent(QDragEnterEvent *event)
{
    const ThingMimeData *tempMimeData = (const ThingMimeData*)event->mimeData();
    const QList<Thing*>* tempList = tempMimeData->thingDragData();
    if(tempList)
    {
        event->accept();
    }
}

void MapWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void MapWidget::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void MapWidget::performDrag()
{
    QDrag *pDrag = new QDrag(this);
    ThingMimeData *pData = new ThingMimeData;
    QList<Thing*> *pList = new QList<Thing*>;
    for(int i = 0; i < m_selectThingsLabel.size(); i++)
    {
        pList->append(m_selectThingsLabel[i]->getData());
    }

    pData->setDragDatas("ThingMimeData",pList);
    pDrag->setMimeData(pData);

    QPixmap pixmap = QPixmap::fromImage(m_selectThingsLabel[0]->getData()->getImage()).scaled(50,50, Qt::IgnoreAspectRatio);
    pDrag->setPixmap(pixmap);

    //inform the mainwindow to show the dragable hex
    QList<mylabel*> templabel;
    for(int i = 0; i < m_selectThingsLabel.size(); i++)
    {
        templabel.push_back(m_selectThingsLabel.at(i));
    }
    emit(startDragSignal(templabel));
    //delete all the selected things when we drag them
    for(int a = 0; a < m_selectThingsLabel.size(); a++)
    {
        for(int i = 0; i < m_thingsLabel.size();)
        {
            if(m_thingsLabel.at(i) == m_selectThingsLabel[a])
            {
                m_thingsLabel.removeAt(i);
            } else {
                i++;
            }
        }
    }
    //delete all the label in the things rack
    qDeleteAll(m_selectThingsLabel);
    m_selectThingsLabel.clear();

    reLayoutIconSlot();

    pDrag->exec(Qt::CopyAction);
}

void MapWidget::dropEvent(QDropEvent *event)
{
    const ThingMimeData *pMimeData = (const ThingMimeData*)event->mimeData();
    const QList<Thing*>* pList = pMimeData->thingDragData();
    if(pList)
    {
        for(int i = 0; i < pList->size(); i++)
        {
            pList->at(i)->setInRack(true);
            mylabel *tempLabel = new mylabel(pList->at(i), this);
            m_thingsLabel.push_back(tempLabel);
        }
        reLayoutIconSlot();
        event->accept();
    }
}

//select multi things' label
void MapWidget::selectThing()
{
    for(int i = 0; i < m_thingsLabel.size(); i++)
    {
        QRect rect = getThingRect(i);
        if(rect.contains(m_mousePressPosn))
        {
            m_thingsLabel[i]->selectThing();
            m_selectThingsLabel.push_back(m_thingsLabel[i]);
        }
    }
}

//unselect one thinglabel depends on the mousepress position
void MapWidget::unSelectThing()
{
    QList<mylabel*>::iterator i = m_selectThingsLabel.begin();
    for(int a = 0; a < m_thingsLabel.size(); a++)
    {
        QRect rect = getThingRect(a);
        if(rect.contains(m_mousePressPosn))
        {
            m_thingsLabel[a]->unSelectedThing();
            for(int b = 0; b < m_selectThingsLabel.size(); b++)
            {
                if(m_selectThingsLabel[b]->getData()->getID() == m_thingsLabel[a]->getData()->getID())
                {
                    m_selectThingsLabel.erase(i + b);
                }
            }
        }
    }
}
