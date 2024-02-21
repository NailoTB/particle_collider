#include "SimulationWindow.h"

SimulationWindow::SimulationWindow(QMainWindow *parent) : QMainWindow(parent), simulationRunning(false)
{
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(Qt::white));

    simulationView = new QGraphicsView(scene, this);
    simulationView->setFixedSize(1400, 800);
    simulationView->setSceneRect(0,0, 1400, 800);
    simulationView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    simulationView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pauseButton = new QPushButton("Start", this);
    resetButton = new QPushButton("Reset", this);
    velocitySlider = new QSlider(Qt::Horizontal, this);

    velocitySlider->setMinimum(-50);
    velocitySlider->setMaximum(50);
    velocitySlider->setValue(0);

    toolbar = new QToolBar(this);
    toolbar->setFloatable(false);
    toolbar->setMovable(false);
    toolbar->addWidget(pauseButton);
    toolbar->addWidget(resetButton);
    toolbar->addWidget(velocitySlider);

    connect(pauseButton, &QPushButton::clicked, this, &SimulationWindow::startPauseButtonClicked);
    connect(resetButton, &QPushButton::clicked, this, &SimulationWindow::clearParticles);

    setCentralWidget(simulationView);
    addToolBar(Qt::RightToolBarArea, toolbar);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulationWindow::updateSimulation);
}

void SimulationWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
    auto xPos = mousePos.x();
    auto yPos = mousePos.y();

    if (event->button() == Qt::LeftButton && xPos < simulationView->width() && !simulationRunning)
    {
        std::vector<std::unique_ptr<Particle>> particleDistribution = Dynamics::generateParticleDistribution(xPos, yPos, 5.0, {(double)velocitySlider->value(), 0, 0}, 10);
        simulationCellSpace->populateCells(particleDistribution);
        redraw();
    }
}

void SimulationWindow::loadCellSpace(CellSpace *cellSpace)
{
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

void SimulationWindow::clearParticles()
{

    if (simulationRunning)
    {
        timer->stop();
        pauseButton->setText("Start");
        simulationRunning = !simulationRunning;
    }
    for (auto item : particleItems)
    {
        scene->removeItem(item);
    }
    particleItems.clear();
    simulationCellSpace->clearCells();
}

void SimulationWindow::flushView()
{
    for (auto item : particleItems)
    {
        scene->removeItem(item);
    }
    particleItems.clear();
    simulationView->viewport()->update();
}

void SimulationWindow::redraw()
{
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

void SimulationWindow::updateSimulation()
{
    for (auto item : particleItems)
    {
        scene->removeItem(item);
    }
    particleItems.clear();

    simulationCellSpace->updateCells(timeStep);
    redraw();
}