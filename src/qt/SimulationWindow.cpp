#include "qt/SimulationWindow.h"

SimulationWindow::SimulationWindow(QMainWindow *parent) : QMainWindow(parent)
{
    scene = new SimulationScene();
    toolbar = new SimulationToolBar();
    connect(toolbar, &SimulationToolBar::pausePressed, this, &SimulationWindow::startPauseButtonClicked);
    connect(toolbar, &SimulationToolBar::clearPressed, this, &SimulationWindow::clearParticles);
    connect(toolbar, &SimulationToolBar::resetPressed, this, &SimulationWindow::generateInitialState);
    connect(scene, &SimulationScene::particleCount, this, &SimulationWindow::updateParticleCountInToolbar);
    setCentralWidget(scene->views()[0]);
    addToolBar(Qt::RightToolBarArea, toolbar);
}
void SimulationWindow::passCellSpaceToScene(CellSpace *cellSpace)
{
    scene->loadCellSpace(cellSpace);
}

void SimulationWindow::updateParticleCountInToolbar(int particleCount)
{
    toolbar->updateParticleCount(particleCount);
}

void SimulationWindow::startPauseButtonClicked(bool run)
{
    scene->setTimerRunState(run);
}

void SimulationWindow::clearParticles()
{
    scene->clearParticles();
}

void SimulationWindow::generateInitialState()
{
    scene->setTimerRunState(false);
    scene->generateInitialState();
}