#include "mylabel.h"

mylabel::mylabel(QWidget *parent) :
    QLabel(parent)
{
}


void mylabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit clicked();
    }
    QLabel::mouseMoveEvent(event);
}
