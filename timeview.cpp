#include "timeview.h"
#include <QLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

TimeView::TimeView(QWidget *parent) : QWidget(parent)
{
    numOfArmo = 0;
    showComponents = false;
    ScaleRange = 15;
    t0 = 0;
    tend = 1;
    tstep = 0.005;

    theSignalColor.setRgb(5,5,5);
    theArmonicColor.setRgb(0,180,0);
    theSinArmonicColor.setRgb(180,0,0);
    theCosArmonicColor.setRgb(0,0,180);

    QLineSeries *segnale = new QLineSeries();
    segnale->setPen(QPen(theSignalColor,3));
    segnale->setName("Signal");
    series.append( segnale );


    Graphico = new QChart();
       Graphico->legend()->hide();
       Graphico->addSeries(series.at(0));
       Graphico->createDefaultAxes();
       Graphico->setTitle("Signal composition");

    chartView = new QChartView(Graphico);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(QSize(800,400));

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(chartView,0,0);

}


int TimeView::addOscillator(QString Name, Oscillator *o)
{
    Source *s= new Source;
    s->Name = Name;
    s->Color = theSignalColor;
    s->Color2 = theSignalColor;
    s->Osc = o;
    sources.append(s);
    connect(o, SIGNAL(paramChanged(float,float,float,bool)), this, SLOT(redraw(float, float, float, bool)));
    redraw();
    numOfArmo++;
    return(sources.size());
}

float TimeView::redraw()
{
    int nSources = sources.size();
    Graphico->removeAllSeries();

    QLineSeries *sourSignal;
    series.clear();

    sourSignal = new QLineSeries();
    sourSignal->setColor(theSignalColor);
    sourSignal->setName("Signal");
    series.append(sourSignal);

    for(int i=0;i<nSources;i++) {
        if(showComponents) {
            sourSignal = new QLineSeries();
            sourSignal->setColor(theSinArmonicColor);
            sourSignal->setName(sources.at(i)->Name+" Sin");
            series.append( sourSignal );
            sourSignal = new QLineSeries();
            sourSignal->setColor(theCosArmonicColor);
            sourSignal->setName(sources.at(i)->Name+" Cos");
            series.append( sourSignal );
        } else {
            sourSignal = new QLineSeries();
            sourSignal->setColor(theArmonicColor);
            sourSignal->setName(sources.at(i)->Name);
            series.append( sourSignal );
        }
    }

    // --------
    int j;
    float newValue, newSignal;
    float t, si, co;

    t = t0;
    while (t<tend) {
        newSignal = 0;
        for(j=0;j<nSources;j++) {
            if(sources.at(j)->Osc->isEnabled()) {
                if(showComponents) {
                    newValue = sources.at(j)->Osc->setTick(t, &si, &co);
                    series.at(j*2+1)->append(t,si);
                    series.at(j*2+2)->append(t,co);
                } else {
                    newValue = sources.at(j)->Osc->setTick(t);
                    series.at(j+1)->append(t,newValue);
                }
                newSignal += newValue;
            }
        }
        series.at(0)->append(t,newSignal);
        t += tstep;
    }

    for(int k=0;k<series.size();k++) {
        Graphico->addSeries(series.at(k));
    }
    Graphico->createDefaultAxes();
    Graphico->axisY()->setRange(-ScaleRange,ScaleRange);
    chartView->repaint();

    return(0);
}
