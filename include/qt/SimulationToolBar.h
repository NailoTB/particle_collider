#ifndef QT_SIMULATIONTOOLBAR_H
#define QT_SIMULATIONTOOLBAR_H

#include <QToolBar>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class SimulationToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit SimulationToolBar(QToolBar *parent = 0);
    double massSliderValue();
    void updateParticleCount(int&);
signals:
    void pausePressed(bool isPaused);
    void clearPressed();
    void resetPressed();
private slots:
    void pauseButtonPressed();
    void clearButtonPressed();
    void resetButtonPressed();
    void flipPauseButtonState();
    void updateMassLabel();
private:
    QPushButton *pauseButton;
    QPushButton *clearButton;
    QPushButton *resetButton;
    QSlider *massSlider;
    QLabel *particleCounter;
    QLabel *massLabel;
};

#endif // QT_SIMULATIONTOOLBAR_H
