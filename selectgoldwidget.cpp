#include "selectgoldwidget.h"

SelectGoldWidget::SelectGoldWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedWidth(80);
    initQlabel();
    //initQComboBox(MaxGold);
    input = new QComboBox(this);
    input->move(0,20);
}

void SelectGoldWidget::refreshGoldValue(int MaxGold)
{
    input->clear();
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
    input->clear();
    emit(selectedGoldSignal(selectedGold));
}

void SelectGoldWidget::initQlabel()
{
    info = new QLabel(this);
    info->setGeometry(0,0,80,20);
    info->setText("Select Gold");
}
