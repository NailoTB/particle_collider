#include "qt/SimulationWindow.h"

SimulationWindow::SimulationWindow(QMainWindow *parent) : QMainWindow(parent)
{
    scene = new SimulationScene();
    toolbar = new SimulationToolBar();

    connect(toolbar, &SimulationToolBar::pausePressed, this, &SimulationWindow::startPauseButtonClicked);
    connect(toolbar, &SimulationToolBar::resetPressed, this, &SimulationWindow::clearParticles);
    connect(scene, &SimulationScene::particleCount, this, &SimulationWindow::updateParticleCountInToolbar);
    setCentralWidget(scene->views()[0]);
    addToolBar(Qt::RightToolBarArea, toolbar);
}
void SimulationWindow::passCellSpaceToScene(CellSpace *cellSpace)
{
    scene->loadCellSpace(cellSpace);
}
void SimulationWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
    auto xPos = mousePos.x();
    auto yPos = mousePos.y();

    if (event->button() == Qt::LeftButton && xPos < scene->views()[0]->width())
    {
        scene->createParticlesOnPoint(xPos, yPos, toolbar->velocitySliderValue());
    }
}

void SimulationWindow::updateParticleCountInToolbar(int particleCount)
{
    toolbar->updateParticleCount(particleCount);
}

void SimulationWindow::startPauseButtonClicked(bool isRunning)
{
    scene->setTimerRunState(isRunning);
}

void SimulationWindow::clearParticles()
{
    scene->clearParticles();
}