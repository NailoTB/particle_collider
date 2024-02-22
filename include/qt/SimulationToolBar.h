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
signals:
    void pausePressed(bool isPaused);
    void resetPressed();
private slots:
    void pauseButtonPressed();
    void resetButtonPressed();
    void flipPauseButtonState();
private:
    QPushButton *pauseButton;
    QPushButton *resetButton;
    QSlider *velocitySlider;
};

#endif // QT_SIMULATIONTOOLBAR_H