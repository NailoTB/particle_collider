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

void SimulationScene::generateInitialState()
{
    clearParticles();
    std::vector<double> velocityP = {70.0, 0.0, 0.0};
    std::vector<double> velocityM = {-70.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Particle>> particleDistribution = Dynamics::generateParticleDistribution(200.0, 400.0, 20.0, velocityP, 200);
    std::vector<std::unique_ptr<Particle>> particleDistributionM = Dynamics::generateParticleDistribution(1200.0, 400.0, 20.0, velocityM, 200);
    simulationCellSpace->populateCells(particleDistribution);
    simulationCellSpace->populateCells(particleDistributionM);
    redraw();
}

void SimulationScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();
    if (event->button() == Qt::LeftButton)
    {
        mouseDragStartPoint = mousePos;
    }
}

void SimulationScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mouseDragEndPoint = event->scenePos();
    if (event->button() == Qt::LeftButton)
    {
        std::vector<double> velocityVector(3, 0.0);

        qreal dragDistance = QLineF(mouseDragStartPoint, mouseDragEndPoint).length();

        if (dragDistance != 0)
        {
            QPointF dragDirection = (mouseDragEndPoint - mouseDragStartPoint) / dragDistance;
            double maxDistance = 200.0;
            double maxFactor = 100.0;
            double normalizedDistanceX = std::min(std::abs(mouseDragEndPoint.x() - mouseDragStartPoint.x()), maxDistance);
            double normalizedDistanceY = std::min(std::abs(mouseDragEndPoint.y() - mouseDragStartPoint.y()), maxDistance);
            double normalizedFactorX = (normalizedDistanceX / maxDistance) * maxFactor;
            double normalizedFactorY = (normalizedDistanceY / maxDistance) * maxFactor;

            velocityVector[0] = normalizedFactorX * dragDirection.x();
            velocityVector[1] = normalizedFactorY * dragDirection.y();
        }

        createParticlesOnPoint(mouseDragStartPoint.x(), mouseDragStartPoint.y(), velocityVector);
    }
}

void SimulationScene::createParticlesOnPoint(const int &xPos, const int &yPos, const std::vector<double> &velocity)
{
    std::vector<std::unique_ptr<Particle>> particleDistribution =
        Dynamics::generateParticleDistribution(xPos, yPos, 5.0, velocity, 10);
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
void SimulationScene::updateParticleCount()
{
    emit particleCount(simulationCellSpace->allParticlePositions().size());
}
