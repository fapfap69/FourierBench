#ifndef OSCILLATORCONTROL_H
#define OSCILLATORCONTROL_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLabel>

class OscillatorControl : public QWidget
{
    Q_OBJECT
public:
    explicit OscillatorControl(QWidget *parent = 0);
    OscillatorControl(const QString aName, QWidget *parent = 0);

    void setParam(float f, float a, float p);

signals:
    void changeParam(float Frequency, float Amplitude, float Phase, bool enab);

public slots:

private:
   //  void __redraw();

private slots:
     void __changeThePhase(double p);
     void __changeTheAmpli(double p);
     void __changeTheSinAmp(double p);
     void __changeTheCosAmp(double p);

     void __changeTheParams();

private:
    QString theName;
  //  QFont theFont;

    float theFrequency;
    float theAmplitude;
    float thePhase;
    float theSinAmp;
    float theCosAmp;

    QColor theColor;

    QLabel *l1;
    QDoubleSpinBox *spinPhase;
    QDoubleSpinBox *spinAmplitude;
    QDoubleSpinBox *spinSin;
    QDoubleSpinBox *spinCos;


};

#endif // OSCILLATORCONTROL_H
