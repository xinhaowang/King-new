#include "mylabel.h"

mylabel::mylabel(QWidget *parent) :
    QLabel(parent)
{
}

mylabel::mylabel(Thing *thingData, QWidget *parent):m_thingData(thingData),QLabel(parent)
{
    m_selected = false;
    m_thingImage = new QLabel(this);
    QSize imageSize;
    QPixmap pixmap;
    if(m_thingData->getMode() == BigIcon_Mode)
    {
        pixmap = QPixmap::fromImage(m_thingData->getImage().scaled(QSize(80,80),
                                                                   Qt::IgnoreAspectRatio));
        imageSize = pixmap.size();
        m_thingImage->setPixmap(pixmap);
        this->setFixedSize(QSize(imageSize.width(),imageSize.height()));
    } else if (m_thingData->getMode() == SmallIcon_Mode) {
        pixmap = QPixmap::fromImage(m_thingData->getImage().scaled(QSize(30,30),
                                                                   Qt::IgnoreAspectRatio));
        imageSize = pixmap.size();
        m_thingImage->setPixmap(pixmap);
        this->setFixedSize(QSize(imageSize.width(),imageSize.height()));
    }

}

mylabel::~mylabel() {
    this->clear();
}

void mylabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
}

void mylabel::paintEvent(QPaintEvent *event)
{
    if(m_selected)
    {
        this->setStyleSheet("border-width: 2px; border-style: solid; border-color:red");
    } else {
        //delete the stylesheet
        this->setStyleSheet("");
    }
    QLabel::paintEvent(event);
}


