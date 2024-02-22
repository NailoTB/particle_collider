#include "qt/SimulationToolBar.h"

SimulationToolBar::SimulationToolBar(QToolBar *parent) : QToolBar(parent)
{
    pauseButton = new QPushButton("Start", this);
    resetButton = new QPushButton("Reset", this);
    velocitySlider = new QSlider(Qt::Horizontal, this);
    particleCounter = new QLabel("Particle Count: 0");

    velocitySlider->setMinimum(-50);
    velocitySlider->setMaximum(50);
    velocitySlider->setValue(0);

    setFloatable(false);
    setMovable(false);
    addWidget(pauseButton);
    addWidget(resetButton);
    addWidget(velocitySlider);
    addWidget(particleCounter);
    connect(pauseButton, &QPushButton::clicked, this, &SimulationToolBar::pauseButtonPressed);
    connect(resetButton, &QPushButton::clicked, this, &SimulationToolBar::resetButtonPressed);
}

void SimulationToolBar::pauseButtonPressed()
{
    flipPauseButtonState();
    emit pausePressed(pauseButton->text() == "Pause"); // Emits isRunning
}
void SimulationToolBar::resetButtonPressed()
{
    if (pauseButton->text() == "Pause")
    {
        pauseButton->setText("Start");
    }
    emit resetPressed();
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