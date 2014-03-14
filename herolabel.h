#ifndef HEROLABEL_H
#define HEROLABEL_H

#include <QLabel>
#include "hero.h"


class HeroLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HeroLabel(QWidget *parent = 0);
    HeroLabel(Hero *heroData, QWidget *parent = 0);
    ~HeroLabel();


    Hero *getData() { return m_heroData; }
    void unSelectedHero() { m_selected = false; }
    void selectHero() { m_selected = true; }
    bool selected() { return m_selected; }

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QLabel          *m_heroImage;
    Hero            *m_heroData;
    bool            m_selected;
    QPoint          m_mousePressPos;
};

#endif // HEROLABEL_H
