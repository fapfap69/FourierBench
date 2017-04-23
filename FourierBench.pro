#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T13:00:21
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FourierBench
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timeview.cpp \
    oscillator.cpp \
    oscillatorcontrol.cpp

HEADERS  += mainwindow.h \
    timeview.h \
    oscillator.h \
    oscillatorcontrol.h

FORMS    += mainwindow.ui
