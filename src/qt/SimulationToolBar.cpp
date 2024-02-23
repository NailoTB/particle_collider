#include "qt/SimulationToolBar.h"

SimulationToolBar::SimulationToolBar(QToolBar *parent) : QToolBar(parent)
{
    pauseButton = new QPushButton("Start", this);
    clearButton = new QPushButton("Clear", this);
    //resetButton = new QPushButton("Reset", this);

    velocitySlider = new QSlider(Qt::Horizontal, this);
    particleCounter = new QLabel("Particle Count: 400");

    velocitySlider->setMinimum(-50);
    velocitySlider->setMaximum(50);
    velocitySlider->setValue(0);

    setFloatable(false);
    setMovable(false);
    addWidget(pauseButton);
    addWidget(clearButton);
    addWidget(velocitySlider);
    addWidget(particleCounter);
    connect(pauseButton, &QPushButton::clicked, this, &SimulationToolBar::pauseButtonPressed);
    connect(clearButton, &QPushButton::clicked, this, &SimulationToolBar::clearButtonPressed);
}

void SimulationToolBar::pauseButtonPressed()
{
    flipPauseButtonState();
    emit pausePressed(pauseButton->text() == "Pause"); // Emits isRunning
}
void SimulationToolBar::clearButtonPressed()
{
    if (pauseButton->text() == "Pause")
    {
        pauseButton->setText("Start");
    }
    emit clearPressed();
}

void SimulationToolBar::flipPauseButtonState()
{
    auto currentText = pauseButton->text();
    if (currentText == "Start")
    {
        pauseButton->setText("Pause");
    }
    else
    {
        pauseButton->setText("Start");
    }
}

int SimulationToolBar::velocitySliderValue()
{
    return velocitySlider->value();
}
void SimulationToolBar::updateParticleCount(int &particleCount)
{
    particleCounter->setText(QString("Particle Count: %1").arg(particleCount));
}