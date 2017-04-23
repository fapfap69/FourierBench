#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QLayout>
#include <QCheckBox>

#include <oscillator.h>
#include "oscillatorcontrol.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    theScaleRange = 15;
    showSinCosComponents = false;


    QFont theFont("Arial",13);
    QColor theColor(0,0,60);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Background, theColor);
    this->setWindowTitle("Fourier Work Bench  v.0  - inFrAnto Software (CopyLeft)");

    // -----------------------
    QWidget *centralW = new QWidget(parent);
    QGridLayout *centralL = new QGridLayout(centralW);

    QHBoxLayout *maincontrolL = new QHBoxLayout();
    maincontrolL->setSpacing(0);
    maincontrolL->setMargin(0);
    maincontrolL->setContentsMargins(5,0,0,0);


    QLabel *l = new QLabel("Scale Range ");
    l->setFont(theFont);
    l->setAutoFillBackground(true);
    l->setPalette(palette);
    l->setMaximumWidth(90);
    maincontrolL->addWidget(l);
    QSpinBox *sp = new QSpinBox();
    sp->setFont(theFont);
    sp->setRange(1,30);
    sp->setValue(theScaleRange);
    sp->setMaximumWidth(90);
    maincontrolL->addWidget(sp);

    QCheckBox *co = new QCheckBox("Show sin() cos() components");
    co->setFont(theFont);
    co->setCheckState(Qt::Unchecked);
    maincontrolL->addWidget(co);

    centralL->addLayout(maincontrolL,0,1);

    QHBoxLayout *benchL = new QHBoxLayout();
    benchL->setSpacing(0);
    benchL->setMargin(0);
    benchL->setContentsMargins(5,0,0,0);

    QVBoxLayout *benchcontrolL = new QVBoxLayout();
    l = new QLabel("Armonics");
    l->setFont(theFont);
    l->setAutoFillBackground(true);
    l->setPalette(palette);
    l->setMaximumWidth(90);
    benchcontrolL->addWidget(l);


    Bench = new TimeView(this);

    Oscillator *osc;
    OscillatorControl *oscont;
    int i,j;
    for(j=0;j<10;j++) {
        osc = new Oscillator(j+1,0,0);
        i = Bench->addOscillator(QString::number(j+1),osc);
        oscont = new OscillatorControl(QString::number(j+1),parent);
        oscont->setParam(j+1,0,0);
        connect(oscont, SIGNAL(changeParam(float,float,float,bool)),osc, SLOT(setParam(float,float,float,bool)));
        Oscillators.append(oscont);
        benchcontrolL->addWidget(oscont);
    }
    benchL->addLayout(benchcontrolL);

    benchL->addWidget(Bench);



    centralL->addLayout(benchL,1,1);

    centralW->setLayout(centralL);
    setCentralWidget(centralW);

    // signal connection
    connect(co, SIGNAL(stateChanged(int)), Bench, SLOT(setShowComponents(int)));
    connect(sp, SIGNAL(valueChanged(int)), Bench, SLOT(setScaleRange(int)));

}

MainWindow::~MainWindow()
{
    //delete ui;
}


