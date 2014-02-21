#ifndef COMBAT_H
#define COMBAT_H

#include <QWidget>

namespace Ui {
class Combat;
}

class Combat : public QWidget
{
    Q_OBJECT

public:
    explicit Combat(QWidget *parent = 0);
    ~Combat();

private:
    Ui::Combat *ui;
};

#endif // COMBAT_H
