#ifndef HEXWIDGET_H
#define HEXWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QMessageBox>
#include "ThingMimeData.h"
#include "hex.h"
#include "mylabel.h"
#include "building.h"
#include "herolabel.h"

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

    vector<mylabel *> thingsLabel() const;
    void setThingsLabel(mylabel *thingsLabel);
    void deleteThingsLabel(QList<mylabel *> tempthingsLabel);

    Hex *hexData() const;
    void setHexData(Hex *hexData);

    HeroLabel *heroLabel() const;
    void setHeroLabel(HeroLabel *heroLabel);

protected:
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);    
    void paintEvent(QPaintEvent *);

signals:
    void hexHasChangedSignal(HexWidget *tempHexWidget);
    void requirePlayerIDnPhaseSignal();
    void setBulidngSingal(HexWidget*);
    void setHeroSignal(HexWidget*);
    void setThingsToMoveWidgetSignal(HexWidget*);
    void sendThingsBackToHex(const QList<Thing*>*);
    void sendbackThingSignal(const QList<Thing*>*);

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
    vector<mylabel *>   m_thingsLabel;
    Building            *m_building;
    HeroLabel           *m_heroLabel;
};

#endif // HEXWIDGET_H
