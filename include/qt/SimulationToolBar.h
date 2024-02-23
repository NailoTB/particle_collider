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
    int velocitySliderValue();
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
private:
    QPushButton *pauseButton;
    QPushButton *clearButton;
    QPushButton *resetButton;
    QSlider *velocitySlider;
    QLabel *particleCounter;
};

#endif // QT_SIMULATIONTOOLBAR_H
