#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAcceptDrops(true);
    m_control = new Control(this);
}

MapWidget::~MapWidget()
{

}

//just for test
void MapWidget::init()
{
    //initial the data in the control
    m_control->init();

    //the board can only has less 10 things
    if(m_control->getSize() <= 10)
    {
        for(size_t i = 0; i < m_control->getSize(); i++)
        {
            mylabel *tempThingLabel = new mylabel(m_control->getThing(i), this);
            m_thingsLabel.push_back(tempThingLabel);
        }
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
    //int height = this->height();
    int itemWidth = m_thingsLabel[index]->width();
    int itemHeight = m_thingsLabel[index]->height();
    int colCount = width/(itemWidth + spacing);
    //int rowCount = height/(itemHeight + spacing);
    int row = index/colCount;
    int col = index%colCount;
    int xPosn = col*(itemWidth + spacing);
    int yPosn = row*(itemHeight + spacing);
    return QRect(xPosn, yPosn, itemWidth, itemHeight);
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    //change the layout if the size has changed
    for(size_t i = 0; i < m_thingsLabel.size(); i++)
    {
        QRect rect = getThingRect(i);
        if(i == m_thingsLabel.size() - 1)
        {
            this->setMinimumHeight(rect.y() + 80);
        }
        m_thingsLabel[i]->setGeometry(rect);
    }
    QWidget::resizeEvent(event);
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    m_mousePressPosn = event->pos();
    //clear all the select things if we press right button
    if(Qt::RightButton == event->button())
    {
        for(size_t i = 0; i < m_selectThingsLabel.size(); i++)
        {
            m_selectThingsLabel[i]->unSelectedThing();
        }
        m_selectThingsLabel.clear();
    } else if (Qt::LeftButton == event->button()) {
        for(size_t i = 0; i < m_thingsLabel.size(); i++)
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
    clear();
    for(size_t i = 0; i < m_control->getSize(); i++)
    {
        mylabel *tempThingLabel = new mylabel(m_control->getThing(i),this);
        m_thingsLabel.push_back(tempThingLabel);
    }
    for(size_t i = 0; i < m_thingsLabel.size(); i++)
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
    qDeleteAll(m_selectThingsLabel);
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

void MapWidget::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void MapWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void MapWidget::performDrag()
{
    QDrag *pDrag = new QDrag(this);
    ThingMimeData *pData = new ThingMimeData;
    QList<Thing*> *pList = new QList<Thing*>;
    for(size_t i = 0; i < m_selectThingsLabel.size(); i++)
    {
        pList->append(m_selectThingsLabel[i]->getData());
    }
    pData->setDragDatas("ThingMimeData",pList);
    pDrag->setMimeData(pData);

    QPixmap pixmap = QPixmap::fromImage(m_selectThingsLabel[0]->getData()->getImage()).scaled(50,50, Qt::IgnoreAspectRatio);
    pDrag->setPixmap(pixmap);
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
            m_control->addThing(pList->at(i));

        }
        reLayoutIconSlot();
        event->accept();
    }
}

//select multi things' label
void MapWidget::selectThing()
{
    for(size_t i = 0; i < m_thingsLabel.size(); i++)
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
    vector<mylabel*>::iterator i = m_selectThingsLabel.begin();
    for(size_t a = 0; a < m_thingsLabel.size(); a++)
    {
        QRect rect = getThingRect(a);
        if(rect.contains(m_mousePressPosn))
        {
            m_thingsLabel[a]->unSelectedThing();
            for(size_t b = 0; b < m_selectThingsLabel.size(); b++)
            {
                if(m_selectThingsLabel[b]->getData()->getID() == m_thingsLabel[a]->getData()->getID())
                {
                    m_selectThingsLabel.erase(i + b);
                }
            }
        }
    }
}
