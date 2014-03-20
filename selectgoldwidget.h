#ifndef SELECTGOLDWIDGET_H
#define SELECTGOLDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QComboBox>

class SelectGoldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectGoldWidget(QWidget *parent = 0);

    void initQlabel();
    void refreshGoldValue(int MaxGold);

signals:
    void selectedGoldSignal(int gold);

public slots:

    void setSelectedGoldSlot(QString temp);
private:
    int         selectedGold;
    QLabel      *info;
    QComboBox   *input;
    QVBoxLayout *layout;

};

#endif // SELECTGOLDWIDGET_H
