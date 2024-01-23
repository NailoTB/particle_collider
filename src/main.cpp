#include "Particle.h"
#include "Boson.h"
#include "Fermion.h"
#include "Dynamics.h"
#include "CellSpace.h"
#include <stdio.h>

// #include <QApplication>
// #include <QGraphicsScene>
// #include <QGraphicsView>
// #include <QGraphicsEllipseItem>
// #include <QTimer>
// #include <QBrush>
// #include <QElapsedTimer>

int main(int argc, char **argv)
{
    // QApplication app(argc, argv);

    CellSpace newspace(10, 10, 0.1);
    std::vector<double> velocity = {0.0, 0.01, 0.0};
    std::vector<std::shared_ptr<Particle>> particleDistribution = Dynamics::generateParticleDistribution(0.5, 0.5, 0.1, velocity, 100);
    newspace.populateCells(particleDistribution, false);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << "Cell: " << i << " " << j << std::endl;
            newspace.grid[i][j].printParticleList();
        }
    }

    // Create a QGraphicsScene and a QGraphicsView
    // QGraphicsScene scene;
    // scene.setBackgroundBrush(QBrush(Qt::white));

    // QGraphicsView view(&scene);
    // view.show();
    // view.resize(800, 600); // Create QGraphicsEllipseItems to represent the particles
    // QGraphicsEllipseItem *photonItem = new QGraphicsEllipseItem(
    // photon.getPosition()[0], photon.getPosition()[1], 3, 3);
    // QGraphicsEllipseItem *electronItem = new QGraphicsEllipseItem(
    // electron.getPosition()[0], electron.getPosition()[1], 10, 10);

    // photonItem->setBrush(QBrush(Qt::yellow)); // Set color for the photon
    // electronItem->setBrush(QBrush(Qt::blue)); // Set color for the electron

    // Add the items to the scene
    // scene.addItem(photonItem);
    // scene.addItem(electronItem);

    // const double dt = 0.000000001; // Time increment
    // QTimer timer;
    // QElapsedTimer elapsedTimer;
    // elapsedTimer.start();
    // QObject::connect(&timer, &QTimer::timeout, [&]()
    // {
    // Dynamics::updatePosition(photon, dt);
    // Dynamics::updatePosition(electron, dt);

    // Update the positions of QGraphicsEllipseItems
    // photonItem->setPos(photon.getPosition()[0], photon.getPosition()[1]);
    // electronItem->setPos(electron.getPosition()[0], electron.getPosition()[1]);

    // view.setSceneRect(electronItem->pos().x() - view.viewport()->width()/2,
    // electronItem->pos().y() - view.viewport()->height()/2,
    // view.viewport()->width(),
    // view.viewport()->height());
    // view.viewport()->update(); });

    // timer.start(10);

    // return app.exec();
    return (0);
}
