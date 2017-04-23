#include "oscillatorcontrol.h"
#include <QLayout>
#include <math.h>

OscillatorControl::OscillatorControl(const QString aName, QWidget *parent) : QWidget(parent)
{

    theFrequency = 1; // default values
    QFont theFont("Arial",11);
    theColor.setRgb(140,0,0);

    QVBoxLayout *mainL = new QVBoxLayout(this);
    mainL->setSpacing(0);
    mainL->setMargin(0);
    mainL->setContentsMargins(0,0,0,0);

    theName = aName;

    l1 = new QLabel(theName,parent);
    l1->setFont(theFont);

    mainL->addWidget(l1);

    QHBoxLayout *lineL;
    QLabel *l;

    lineL = new QHBoxLayout();

    l = new QLabel("Ampli.", parent);
    l->setFont(theFont);
    l->setMaximumWidth(40);
    l->setFixedWidth(50);
    lineL->addWidget(l);

    spinAmplitude = new QDoubleSpinBox(parent);
    spinAmplitude->setFont(theFont);
    spinAmplitude->setRange(0.0, 10.0 );
    spinAmplitude->setDecimals(2);
    spinAmplitude->setSingleStep(0.1);
    spinAmplitude->setValue(thePhase);
    spinAmplitude->setMaximumWidth(40);
    spinAmplitude->setFixedWidth(50);
    lineL->addWidget(spinAmplitude);

    l = new QLabel("Phase", parent);
    l->setFont(theFont);
    l->setMaximumWidth(40);
    l->setFixedWidth(50);
    lineL->addWidget(l);

    spinPhase = new QDoubleSpinBox(parent);
    spinPhase->setFont(theFont);
    spinPhase->setRange(0.0, atan(1)*8 );
    spinPhase->setDecimals(2);
    spinPhase->setSingleStep(0.1);
    spinPhase->setValue(thePhase);
    spinPhase->setMaximumWidth(40);
    spinPhase->setFixedWidth(50);
    lineL->addWidget(spinPhase);

    mainL->addLayout(lineL);

    lineL = new QHBoxLayout();

    l = new QLabel("Sin Am.", parent);
    l->setFont(theFont);
    l->setMaximumWidth(40);
    l->setFixedWidth(50);
    lineL->addWidget(l);

    spinSin = new QDoubleSpinBox(parent);
    spinSin->setFont(theFont);
    spinSin->setRange(0.0, 10.0 );
    spinSin->setDecimals(2);
    spinSin->setSingleStep(0.1);
    spinSin->setValue(theSinAmp);
    spinSin->setMaximumWidth(40);
    spinSin->setFixedWidth(50);
    lineL->addWidget(spinSin);

    l = new QLabel("Cos Am.", parent);
    l->setFont(theFont);
    l->setMaximumWidth(40);
    l->setFixedWidth(50);
    lineL->addWidget(l);

    spinCos = new QDoubleSpinBox(parent);
    spinCos->setFont(theFont);
    spinCos->setRange(0.0, 10 );
    spinCos->setDecimals(2);
    spinCos->setSingleStep(0.1);
    spinCos->setValue(theCosAmp);
    spinCos->setMaximumWidth(40);
    spinCos->setFixedWidth(50);
    lineL->addWidget(spinCos);

    mainL->addLayout(lineL);



    mainL->addStretch();

    connect(spinPhase, SIGNAL(valueChanged(double)), this, SLOT(__changeThePhase(double)) );
    connect(spinAmplitude, SIGNAL(valueChanged(double)), this, SLOT(__changeTheAmpli(double)) );
    connect(spinSin, SIGNAL(valueChanged(double)), this, SLOT(__changeTheSinAmp(double)) );
    connect(spinCos, SIGNAL(valueChanged(double)), this, SLOT(__changeTheCosAmp(double)) );


}

void OscillatorControl::setParam(float f, float a, float p)
{
    bool isChanged = false;
    theFrequency = f;
    if(theAmplitude != a) {
        theAmplitude = a;
        isChanged = true;
    }
    if(thePhase != p) {
        thePhase = p;
        isChanged = true;
    }
    if(isChanged) {
        theSinAmp = theAmplitude * sin(thePhase);
        theCosAmp = theAmplitude * cos(thePhase);
        __changeTheParams();
    }
}

void OscillatorControl::__changeThePhase(double p)
{
   if(thePhase != p) {
       thePhase = p;
       theSinAmp = theAmplitude * sin(thePhase);
       theCosAmp = theAmplitude * cos(thePhase);
       __changeTheParams();
   }
}

void OscillatorControl::__changeTheAmpli(double p)
{
    if(theAmplitude != p) {
        theAmplitude = p;
        theSinAmp = theAmplitude * sin(thePhase);
        theCosAmp = theAmplitude * cos(thePhase);
        __changeTheParams();
    }
}

void OscillatorControl::__changeTheSinAmp(double p)
{
    if(theSinAmp != p) {
        theSinAmp = p;
        theAmplitude = sqrt(theSinAmp*theSinAmp + theCosAmp*theCosAmp);
        float ph =atan( theSinAmp / theCosAmp);
        if(theCosAmp<0) ph += atan(1.0)*4;
        else if(theSinAmp<0) ph += atan(1.0)*8;
        thePhase = ph;
        __changeTheParams();
    }
}

void OscillatorControl::__changeTheCosAmp(double p)
{
    if(theCosAmp != p) {
        theCosAmp = p;
        theAmplitude = sqrt(theSinAmp*theSinAmp + theCosAmp*theCosAmp);
        float ph =atan( theSinAmp / theCosAmp);
        if(theCosAmp<0) ph += atan(1.0)*4;
        else if(theSinAmp<0) ph += atan(1.0)*8;
        thePhase = ph;
        __changeTheParams();
    }
}

void OscillatorControl::__changeTheParams()
{
    spinAmplitude->setValue(theAmplitude);
    spinPhase->setValue(thePhase);
    spinSin->setValue(theSinAmp);
    spinCos->setValue(theCosAmp);
    emit changeParam(theFrequency, theAmplitude, thePhase, true);

}
