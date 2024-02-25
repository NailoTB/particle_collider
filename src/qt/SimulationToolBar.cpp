#include "qt/SimulationToolBar.h"

SimulationToolBar::SimulationToolBar(QToolBar *parent) : QToolBar(parent)
{
    pauseButton = new QPushButton("Start", this);
    clearButton = new QPushButton("Clear", this);
    resetButton = new QPushButton("Reset", this);

    //velocitySlider = new QSlider(Qt::Horizontal, this);
    particleCounter = new QLabel("Particles: 400");

    // velocitySlider->setMinimum(-50);
    // velocitySlider->setMaximum(50);
    // velocitySlider->setValue(0);

    setFloatable(false);
    setMovable(false);
    addWidget(pauseButton);
    addWidget(clearButton);
    addWidget(resetButton);
    //addWidget(velocitySlider);
    addWidget(particleCounter);
    connect(pauseButton, &QPushButton::clicked, this, &SimulationToolBar::pauseButtonPressed);
    connect(clearButton, &QPushButton::clicked, this, &SimulationToolBar::clearButtonPressed);
    connect(resetButton, &QPushButton::clicked, this, &SimulationToolBar::resetButtonPressed);
}

void SimulationToolBar::pauseButtonPressed()
{
    bool startRunning = pauseButton->text() == "Start";
    flipPauseButtonState();
    emit pausePressed(startRunning); // Emits startRunning
}

void SimulationToolBar::clearButtonPressed()
{
    if (pauseButton->text() == "Pause")
    {
        pauseButton->setText("Start");
    }
    emit clearPressed();
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

// int SimulationToolBar::velocitySliderValue()
// {
//     return velocitySlider->value();
// }
void SimulationToolBar::updateParticleCount(int &particleCount)
{
    particleCounter->setText(QString("Particles: %1").arg(particleCount));
}