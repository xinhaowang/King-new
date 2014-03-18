#include "herolabel.h"

HeroLabel::HeroLabel(QWidget *parent) :
    QLabel(parent)
{
}

HeroLabel::HeroLabel(Hero *heroData, QWidget *parent):m_heroData(heroData),QLabel(parent)
{
    m_selected = false;
    m_heroImage = new QLabel(this);
    QSize imageSize;
    QPixmap pixmap;
    QImage Image= QImage(heroData->getUrl());
    if(m_heroData->getMode() == BigIcon_Mode)
    {
        pixmap = QPixmap::fromImage(Image.scaled(QSize(80,80),Qt::IgnoreAspectRatio));
        imageSize = pixmap.size();
        m_heroImage->setPixmap(pixmap);
        this->setFixedSize(QSize(imageSize.width(),imageSize.height()));
    } else if(m_heroData->getMode() == SmallIcon_Mode)
    {
        pixmap = QPixmap::fromImage(Image.scaled(QSize(30,30),Qt::IgnoreAspectRatio));
        imageSize = pixmap.size();
        m_heroImage->setPixmap(pixmap);
        this->setFixedSize(QSize(imageSize.width(),imageSize.height()));
    }
}

HeroLabel::~HeroLabel() {}

void HeroLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
}

void HeroLabel::paintEvent(QPaintEvent *event)
{
    if(m_selected)
    {
        this->setStyleSheet("border-width: 2px; border-style: solid; border-color:red");
    } else {
        this->setStyleSheet("");
    }
    QLabel::paintEvent(event);
}
