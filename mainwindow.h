#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timeview.h"
#include "oscillatorcontrol.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    int theScaleRange;
    bool showSinCosComponents;


    TimeView *Bench;
    QList<OscillatorControl *> Oscillators;
};

#endif // MAINWINDOW_H
