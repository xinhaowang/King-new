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
    void initThingToRackSlot(vector<Thing*> tempThings);

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
    bool isInVector(mylabel *tempThingLabel);

signals:
    void startDragSignal();
private:
    int                 iconMode;
    vector<mylabel*>    m_thingsLabel;
    vector<mylabel*>    m_selectThingsLabel;
    QPoint              m_mousePressPosn;
    QPoint              m_mousePosn;

public slots:

};

#endif // MAPWIDGET_H
