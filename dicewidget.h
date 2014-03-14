#ifndef DICEWIDGET_H
#define DICEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QMovie>
#include <QtGlobal>
#include <QTime>

class DiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DiceWidget(QWidget *parent = 0);
    ~DiceWidget();

private slots:
    void roll();

private:
    bool rollingFlag;
    QString bgfile;
    QMovie *bgMovie;
    QPushButton *rollButton;
    QLabel *diceLabel;
    QVBoxLayout *layout;
};

#endif // DICEWIDGET_H
