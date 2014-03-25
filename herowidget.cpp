#include "herowidget.h"

HeroWidget::HeroWidget(QWidget *parent) :
    QWidget(parent)
{
}

HeroWidget::~HeroWidget()
{

}

void HeroWidget::initHeroToWidgetSlot(QList<Hero *> tempHeros)
{
    clear();    
    for(int i = 0; i < tempHeros.size(); i++)
    {
        HeroLabel *tempHeroLabel = new HeroLabel(tempHeros.at(i), this);
        m_heroLabel.push_back(tempHeroLabel);
    }
    for(int i = 0; i < m_heroLabel.size(); i++)
    {
        QRect rect = getHeroRect(i);
        m_heroLabel.at(i)->setGeometry(rect);
        m_heroLabel.at(i)->show();
    }
}

void HeroWidget::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        bool chooseFlag = false;
        for(int i = 0; i < m_heroLabel.size(); i++)
        {
            if(m_heroLabel.at(i)->selected())
            {
                chooseFlag = true;
            }
        }
        for(int i = 0; i < m_heroLabel.size(); i++)
        {
            QRect rect = getHeroRect(i);
            if(rect.contains(event->pos()))
            {
                if(m_heroLabel.at(i)->selected())
                {
                    m_heroLabel.at(i)->unSelectedHero();
                } else {
                    if(chooseFlag)
                    {
                        //do nothing
                    } else {
                        m_heroLabel.at(i)->selectHero();
                        emit(heroConfirmSignal(m_heroLabel.at(i)->getData()));
                    }
                }
            }
        }
        update();
    }
    QWidget::mousePressEvent(event);
}

QRect HeroWidget::getHeroRect(int index)
{
    if(index < 0 || index > m_heroLabel.size())
    {
        return QRect();
    }
    const int spacing = 10;
    int width = this->width();
    int itemWidth = m_heroLabel.at(index)->width();
    int itemHeight = m_heroLabel.at(index)->height();
    int colCount = width/(itemWidth + spacing);
    int row = index/colCount;
    int col = index%colCount;
    int xPosn = col*(itemWidth + spacing);
    int yPosn = row*(itemHeight + spacing);
    return QRect(xPosn, yPosn, itemWidth, itemHeight);
}

void HeroWidget::clear()
{
    qDeleteAll(m_heroLabel);
    m_heroLabel.clear();
}

void HeroWidget::reLayoutIconSlot()
{
    for(int i = 0; i < m_heroLabel.size(); i++)
    {
        QRect rect = getHeroRect(i);
        m_heroLabel.at(i)->setGeometry(rect);
        m_heroLabel.at(i)->show();
    }
    this->repaint();
}
