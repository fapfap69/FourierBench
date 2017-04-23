#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QLayout>
#include <oscillator.h>

QT_CHARTS_USE_NAMESPACE

class TimeView : public QWidget
{
    Q_OBJECT
private:
    struct Source {
        QString Name;
        Oscillator *Osc;
        QColor Color;
        QColor Color2;

    };

public:
    explicit TimeView(QWidget *parent = 0);
    int addOscillator(QString Name, Oscillator *o);

signals:

public slots:
    float redraw();
    void redraw(float f, float a, float p, bool e) { redraw(); }
    void setShowComponents(int c) { showComponents = c==Qt::Unchecked ?  false : true ; redraw(); }
    void setScaleRange(int s) { ScaleRange = s; redraw(); }


private:
    int numOfArmo;
    QList<Source *>sources;

    float Time;
    float Value;

    float t0;
    float tend;
    float tstep;

    bool showComponents;
    float ScaleRange;

    QColor theSignalColor;
    QColor theArmonicColor;
    QColor theSinArmonicColor;
    QColor theCosArmonicColor;

    QList<QLineSeries*> series;

    QChart *Graphico;
    QChartView *chartView;
    QGridLayout *gridLayout;

};

#endif // TIMEVIEW_H
