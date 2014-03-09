#ifndef HEXWIDGET_H
#define HEXWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include "ThingMimeData.h"
#include "hex.h"
#include "mylabel.h"
#include "building.h"

class HexWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HexWidget(QWidget *parent = 0);
    HexWidget(QWidget *parent, Hex *tempHex);

    void refreshMyLabel();
    int getID() const;
    void setID(int value);

    bool getIsEnableDrag() const;
    void setIsEnableDrag(bool value);

    bool getIsEnabledClick() const;
    void setIsEnabledClick(bool value);

    int getSelectState() const;
    void setSelectState(int value);

    Building *building() const;
    void setBuilding(Building *building);

protected:
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);    
    void paintEvent(QPaintEvent *);

signals:
    void hexHasChangedSignal(HexWidget *tempHexWidget);
    void requirePlayerIDnPhaseSignal();
    void setBulidngSingal(HexWidget*);

public slots:
    void setPlayerIDnPhaseSlot(int tempPlayerID, int tempPhase);

private:
    int                 ID;
    int                 playerID;
    int                 phase;
    int                 SelectState;
    bool                isEnableDrag;
    bool                isEnabledClick;
    QString             oldStyle;
    Hex                 *m_hexData;
    vector<mylabel*>    m_thingsLabel;
    Building*           m_building;
};

#endif // HEXWIDGET_H
