#include "thingsdropwidget.h"

ThingsDropWidget::ThingsDropWidget(QWidget *parent):QWidget(parent)
{
    this->setAcceptDrops(true);
    //set the stylesheet
    this->setStyleSheet("background-color:white;");
}

ThingsDropWidget::~ThingsDropWidget()
{

}

void ThingsDropWidget::setDropBox()
{
    QLabel *textLabel = new QLabel(this);
    textLabel->setFixedSize(100,100);
    textLabel->move(0,0);
    textLabel->setText("DropBox");
}

void ThingsDropWidget::setTradeBox()
{
    QLabel *textLabel = new QLabel(this);
    textLabel->setFixedSize(100,100);
    textLabel->move(0,0);
    textLabel->setText("TradeBox");
}

void ThingsDropWidget::dragEnterEvent(QDragEnterEvent *event)
{
    const ThingMimeData *tempMimeData = (const ThingMimeData*)event->mimeData();
    const QList<Thing*>* tempList = tempMimeData->thingDragData();
    if(tempList)
    {
        event->accept();
    }
}

void ThingsDropWidget::dropEvent(QDropEvent *event)
{
    const ThingMimeData *pMimeData = (const ThingMimeData*)event->mimeData();
    const QList<Thing*>* pList = pMimeData->thingDragData();
    QList<Thing*> tempList;
    if(pList)
    {
        for(int i = 0; i < pList->size(); i++)
        {
            tempList.push_back(pList->at(i));
        }
        event->accept();
    }
    emit(tradeThingsSignal(tempList));
}


