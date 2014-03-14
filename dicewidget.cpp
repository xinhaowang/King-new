#include "dicewidget.h"

DiceWidget::DiceWidget(QWidget *parent) :
    QWidget(parent)
{
    rollingFlag = false;
    bgfile = ":/background/image/background/dice.png";
    bgMovie = new QMovie(":/background/image/background/dice_roll.gif");
    diceLabel = new QLabel;
    diceLabel->setMovie(bgMovie);
    diceLabel->setPixmap(QPixmap(bgfile));
    rollButton = new QPushButton(tr("Roll"));
    layout = new QVBoxLayout;
    layout->addWidget(diceLabel);
    layout->addWidget(rollButton);
    setLayout(layout);
    connect(rollButton, SIGNAL(clicked()), this, SLOT(roll()));
}

DiceWidget::~DiceWidget(){
    delete bgMovie;
    delete diceLabel;
    delete rollButton;
    delete layout;
}

void DiceWidget::roll(){
    if(!rollingFlag){
        rollingFlag = true;
        rollButton->setText(tr("Stop"));
        diceLabel->setMovie(bgMovie);
        bgMovie->start();
        qsrand(QDateTime::currentDateTime().toTime_t());
    }else{
        rollingFlag = false;
        rollButton->setText(tr("Roll"));
        diceLabel->setMovie(bgMovie);
        bgMovie->stop();
        int k = qrand() % 6 + 1;
        bgfile.replace(34, 5, QChar(k));
        diceLabel->setPixmap(bgfile);
    }
}
