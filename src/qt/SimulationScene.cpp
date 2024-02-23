#include "qt/SimulationScene.h"

SimulationScene::SimulationScene(QGraphicsScene *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(Qt::white));

    simulationView = new QGraphicsView(this);
    simulationView->setFixedSize(1400, 800);
    simulationView->setSceneRect(0, 0, 1400, 800);
    simulationView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    simulationView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    simulationTimer = new QTimer(this);
    particleCountTimer = new QTimer(this);
    particleCountTimer->start(100);
    connect(simulationTimer, &QTimer::timeout, this, &SimulationScene::updateParticlePositions);
    connect(particleCountTimer, &QTimer::timeout, this, &SimulationScene::updateParticleCount);
}

void SimulationScene::loadCellSpace(CellSpace *cellSpace)
{
    simulationCellSpace = cellSpace;
    redraw();
}

void SimulationScene::createParticlesOnPoint(const int &xPos, const int &yPos, const int &velocity)
{
    std::vector<std::unique_ptr<Particle>> particleDistribution =
        Dynamics::generateParticleDistribution(xPos, yPos, 5.0, {(double)velocity, 0, 0}, 10);
    simulationCellSpace->populateCells(particleDistribution);
    redraw();
}

void SimulationScene::clearPreviousParticleGraphics()
{
    for (auto item : previousTimestepParticleGraphics)
    {
        removeItem(item);
    }
    previousTimestepParticleGraphics.clear();
}

void SimulationScene::setTimerRunState(bool state)
{
    state ? simulationTimer->start(10) : simulationTimer->stop();
}

void SimulationScene::updateParticlePositions()
{
    clearPreviousParticleGraphics();
    simulationCellSpace->updateCells(timeStep);
    redraw();
}

void SimulationScene::clearParticles()
{

    simulationTimer->stop();
    clearPreviousParticleGraphics();
    simulationCellSpace->clearCells();
}

void SimulationScene::flushView()
{
    clearPreviousParticleGraphics();
    simulationView->viewport()->update();
}

void SimulationScene::redraw()
{
    std::vector<std::vector<double>> posMatrix = simulationCellSpace->allParticlePositions();

    for (auto pos : posMatrix)
    {
        QGraphicsEllipseItem *particleItem = new QGraphicsEllipseItem(pos[0], pos[1], 3, 3);
        particleItem->setBrush(QBrush(Qt::blue));
        addItem(particleItem);
        previousTimestepParticleGraphics.append(particleItem);
    }
    simulationView->viewport()->update();
}
void SimulationScene::updateParticleCount(){
    emit particleCount(simulationCellSpace->allParticlePositions().size());
}
