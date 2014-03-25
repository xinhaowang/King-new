#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>
#include <QRect>
#include <QDrag>
#include "ThingMimeData.h"
#include "thing.h"
#include "mylabel.h"

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = 0);
    ~MapWidget();

public slots:
    void initThingToRackSlot(QList<Thing*> tempThings);

private slots:
    void reLayoutIconSlot();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

    QRect getThingRect(int index);
    void clear();
    void performDrag();
    void selectThing();
    void unSelectThing();
    bool isInQList(mylabel *tempThingLabel);

signals:
    void startDragSignal(QList<mylabel*>);

private:
    int                 iconMode;
    QList<mylabel*>    m_thingsLabel;
    QList<mylabel*>    m_selectThingsLabel;
    QPoint              m_mousePressPosn;
    QPoint              m_mousePosn;

public slots:

};

#endif // MAPWIDGET_H
