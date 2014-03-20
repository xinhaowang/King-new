#ifndef THINGSDROPWIDGET_H
#define THINGSDROPWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QDrag>
#include "ThingMimeData.h"
class ThingsDropWidget : public QWidget
{
    Q_OBJECT
public:
    ThingsDropWidget(QWidget *parent = 0);
    ~ThingsDropWidget();

    void setDropBox();
    void setTradeBox();
signals:
    void tradeThingsSignal(QList<Thing*>);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // THINGSDROPWIDGET_H
