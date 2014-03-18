#include "selectgoldwidget.h"

SelectGoldWidget::SelectGoldWidget(QWidget *parent) :
    QWidget(parent)
{
}

SelectGoldWidget::SelectGoldWidget(QWidget *parent, int MaxGold) :
    QWidget(parent)
{
    initQlabel();
    initQComboBox(MaxGold);
}

void SelectGoldWidget::initQComboBox(int MaxGold)
{
    input = new QComboBox(this);
    input->setGeometry(0,20,80,20);
    int count = MaxGold / 5;
    for(int i = 0; i <= count; i++)
    {
        input->addItem(QString::number(i*5));
    }
    connect(input, SIGNAL(activated(QString)), this, SLOT(setSelectedGoldSlot(QString)));
}

void SelectGoldWidget::setSelectedGoldSlot(QString temp)
{
    selectedGold = temp.toInt();
    emit(selectedGoldSignal(selectedGold));
}

void SelectGoldWidget::initQlabel()
{
    info = new QLabel(this);
    info->setGeometry(0,0,80,20);
    info->setText("Select Gold");
}
