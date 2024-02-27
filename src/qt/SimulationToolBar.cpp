#include "qt/SimulationToolBar.h"

SimulationToolBar::SimulationToolBar(QToolBar *parent) : QToolBar(parent)
{
    pauseButton = new QPushButton("Start", this);
    clearButton = new QPushButton("Clear", this);
    resetButton = new QPushButton("Reset", this);

    particleCounter = new QLabel("Particles: 400");

    massLabel = new QLabel("Mass: 0.5 MeV");
    massSlider = new QSlider(Qt::Horizontal, this);

    massSlider->setMinimum(1);
    massSlider->setMaximum(20);
    massSlider->setValue(5);

    auto separator = new QLabel("New particles:");

    setFloatable(false);
    setMovable(false);
    addWidget(pauseButton);
    addWidget(clearButton);
    addWidget(resetButton);
    addWidget(particleCounter);
    addSeparator();
    addWidget(separator);
    addWidget(massLabel);
    addWidget(massSlider);

    connect(pauseButton, &QPushButton::clicked, this, &SimulationToolBar::pauseButtonPressed);
    connect(clearButton, &QPushButton::clicked, this, &SimulationToolBar::clearButtonPressed);
    connect(resetButton, &QPushButton::clicked, this, &SimulationToolBar::resetButtonPressed);
    connect(massSlider, &QSlider::valueChanged, this, &SimulationToolBar::updateMassLabel);

}

void SimulationToolBar::pauseButtonPressed()
{
    bool startRunning = pauseButton->text() == "Start";
    flipPauseButtonState();
    emit pausePressed(startRunning);
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

double SimulationToolBar::massSliderValue()
{
    double massSliderValueScaled = (double)massSlider->value() * 0.1;
    return massSliderValueScaled;
}
void SimulationToolBar::updateParticleCount(int &particleCount)
{
    particleCounter->setText(QString("Particles: %1").arg(particleCount));
}

void SimulationToolBar::updateMassLabel()
{
    QString formattedMass = QString::number(massSliderValue(), 'f', 1);
    massLabel->setText(QString("Mass: %1 MeV").arg(formattedMass));
}