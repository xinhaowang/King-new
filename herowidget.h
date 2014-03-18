#ifndef HEROWIDGET_H
#define HEROWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include <QList>
#include "hero.h"
#include "herolabel.h"

class HeroWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HeroWidget(QWidget *parent = 0);
    ~HeroWidget();

public slots:
    void initHeroToWidgetSlot(QList<Hero*> tempHeros);

signals:
    void heroConfirmSignal(Hero*);

protected:
    void mousePressEvent(QMouseEvent *event);

    QRect getHeroRect(int index);
    void clear();

private slots:
    void reLayoutIconSlot();

private:
    QList<HeroLabel*>            m_heroLabel;
};

#endif // HEROWIDGET_H
