#ifndef SIMULATIONTOOLBAR_H
#define SIMULATIONTOOLBAR_H

#include <QApplication>
#include <QTimer>
#include <QToolBar>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include "CellSpace.h"

class SimulationToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit SimulationToolBar(QToolBar *parent = 0);
    int velocitySliderValue();
signals:
    void pausePressed();
    void resetPressed();
private slots:
    void pauseButtonPressed();
    void resetButtonPressed();
    void flipPauseButtonState();
private:

    QTimer *timer;
    QPushButton *pauseButton;
    QPushButton *resetButton;
    QSlider *velocitySlider;
    bool simulationRunning;
};

#endif // SIMULATIONTOOLBAR_H
