#include "Particle.h"
#include "Boson.h"
#include "Fermion.h"
#include "Dynamics.h"
#include "CellSpace.h"
#include <stdio.h>
#include <memory>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QBrush>
#include <QElapsedTimer>

int main(int argc, char **argv)
{

    CellSpace newspace(10, 10, 100.0);
    std::vector<double> velocityP = {25.0, 0.0, 0.0};
    std::vector<double> velocityM = {0.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Particle>> particleDistribution = Dynamics::generateParticleDistribution(200.0, 200.0, 15.0, velocityP, 20);
    std::vector<std::unique_ptr<Particle>> particleDistributionM = Dynamics::generateParticleDistribution(500.0, 200.0, 20.0, velocityM, 30);

    // Move to Cells
    // Out of CellSpace -> automatic removal
    newspace.populateCells(particleDistribution);
    newspace.populateCells(particleDistributionM);

    QApplication app(argc, argv);

    // Create a QGraphicsScene and a QGraphicsView
    QGraphicsScene scene;
    scene.setBackgroundBrush(QBrush(Qt::white));

    QGraphicsView view(&scene);
    view.show();
    view.resize(1200, 800);                       // Create QGraphicsEllipseItems to represent the particles
    QList<QGraphicsEllipseItem *> particleItems; // Keep track of particle items
    const double dt = 0.01;                      // Time increment
    QTimer timer;
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();

    QObject::connect(&timer, &QTimer::timeout, [&]()
                     {

    // Remove old particle items from the scene
    for (auto item : particleItems) {
        scene.removeItem(item);
        delete item; // Free memory
    }
    particleItems.clear(); // Clear the list of particle items

    // Update cell space

    newspace.updateCells(dt);
    auto posMatrix = newspace.allParticlePositions();

    // Add new particle items to the scene
    for (auto pos : posMatrix){
        QGraphicsEllipseItem *particleItem = new QGraphicsEllipseItem(pos[0], pos[1], 3, 3);
        particleItem->setBrush(QBrush(Qt::blue));
        scene.addItem(particleItem);
        particleItems.append(particleItem);
    }
    view.viewport()->update(); });

    timer.start(10);

    return app.exec();
}
