#include "SimulationWindow.h"

SimulationWindow::SimulationWindow(QMainWindow *parent) : QMainWindow(parent), simulationRunning(false)
{
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(Qt::white));

    simulationView = new QGraphicsView(scene, this);

    pauseButton = new QPushButton("Start", this);

    QToolBar *toolbar = new QToolBar;
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    toolbar->addWidget(pauseButton);
    connect(pauseButton, &QPushButton::clicked, this, &SimulationWindow::startPauseButtonClicked);
    setCentralWidget(simulationView);
    addToolBar(Qt::RightToolBarArea, toolbar);

    resize(1400, 800);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulationWindow::updateSimulation);
}

void SimulationWindow::loadCellSpace(CellSpace* cellSpace){
    simulationCellSpace = cellSpace;
}

void SimulationWindow::startPauseButtonClicked()
{

    if (simulationRunning)
    {
        timer->stop();
        pauseButton->setText("Start");
    }
    else
    {
        timer->start(10);
        pauseButton->setText("Pause");
    }
    simulationRunning = !simulationRunning;
}

void SimulationWindow::updateSimulation()
{
    for (auto item : particleItems)
    {
        scene->removeItem(item);
    }
    particleItems.clear();

    simulationCellSpace->updateCells(timeStep);
    auto posMatrix = simulationCellSpace->allParticlePositions();

    for (auto pos : posMatrix)
    {
        QGraphicsEllipseItem *particleItem = new QGraphicsEllipseItem(pos[0], pos[1], 3, 3);
        particleItem->setBrush(QBrush(Qt::blue));
        scene->addItem(particleItem);
        particleItems.append(particleItem);
    }
    simulationView->viewport()->update();
}