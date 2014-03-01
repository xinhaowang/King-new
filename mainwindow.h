#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mapwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setBackground();
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    MapWidget       *Things_rack;
    MapWidget       *Hex_1;
};

#endif // MAINWINDOW_H
