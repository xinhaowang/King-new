#ifndef HEXWIDGET_H
#define HEXWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include "ThingMimeData.h"
#include "hex.h"
#include "mylabel.h"

class HexWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HexWidget(QWidget *parent = 0);
    HexWidget(QWidget *parent, Hex *tempHex);

    void refreshMyLabel();
protected:
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);    
    void paintEvent(QPaintEvent *);

signals:
    void hexHasChangedSignal(HexWidget *tempHexWidget);
    void requirePlayerIDSignal();

public slots:
    void setPlayerIDSlot(int tempPlayerID);

private:
    int                 playerID;
    Hex                 *m_hexData;
    vector<mylabel*>    m_thingsLabel;
};

#endif // HEXWIDGET_H
