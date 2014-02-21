#include "combat.h"
#include "ui_combat.h"

Combat::Combat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Combat)
{
    ui->setupUi(this);
}

Combat::~Combat()
{
    delete ui;
}
