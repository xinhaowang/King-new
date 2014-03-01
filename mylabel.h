#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include "thing.h"

using namespace std;

class mylabel : public QLabel
{
    Q_OBJECT
public:
    explicit mylabel(QWidget *parent = 0);
    mylabel(Thing *thingData, QWidget *parent = 0);
    ~mylabel();

    void unSelectedThing(){ m_selected = false; }
    void selectThing(){ m_selected = true;  }
    bool selected() { return m_selected; }
    Thing *getData() {  return m_thingData; }

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QLabel              *m_thingImage;
    Thing               *m_thingData;
    bool                m_selected;
    QPoint              m_mousePressPos;

};

#endif // MYLABEL_H
