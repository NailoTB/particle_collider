#include "qt/SimulationScene.h"

SimulationScene::SimulationScene(QGraphicsScene *parent) : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(Qt::white));

    simulationView = new QGraphicsView(this);
    simulationView->setFixedSize(1400, 800);
    simulationView->setSceneRect(0, 0, 1400, 800);
    simulationView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    simulationView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulationScene::updateParticlePositions);
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

void SimulationScene::clearParticleItems()
{
    for (auto item : particleItems)
    {
        removeItem(item);
    }
    particleItems.clear();
}

void SimulationScene::setTimerRunState(bool state)
{
    state ? timer->start(10) : timer->stop();
}

void SimulationScene::updateParticlePositions()
{
    clearParticleItems();
    simulationCellSpace->updateCells(timeStep);
    redraw();
}

void SimulationScene::clearParticles()
{

    timer->stop();
    clearParticleItems();
    simulationCellSpace->clearCells();
}

void SimulationScene::flushView()
{
    clearParticleItems();
    simulationView->viewport()->update();
}

void SimulationScene::redraw()
{
    auto posMatrix = simulationCellSpace->allParticlePositions();

    for (auto pos : posMatrix)
    {
        QGraphicsEllipseItem *particleItem = new QGraphicsEllipseItem(pos[0], pos[1], 3, 3);
        particleItem->setBrush(QBrush(Qt::blue));
        addItem(particleItem);
        particleItems.append(particleItem);
    }
    simulationView->viewport()->update();
}
