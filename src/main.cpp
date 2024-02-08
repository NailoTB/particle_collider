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
    //TODO: gridSize Dependent on interaction length
    double gridSize = 10;
    int xGridSpan = 300;
    int yGridSpan = 100;
    CellSpace newspace(xGridSpan, yGridSpan, gridSize);
    std::vector<double> velocityP = {70.0, 0.0, 0.0};
    std::vector<double> velocityM = {-70.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Particle>> particleDistribution = Dynamics::generateParticleDistribution(200.0, 500.0, 10.0, velocityP, 50);
    std::vector<std::unique_ptr<Particle>> particleDistributionM = Dynamics::generateParticleDistribution(500.0, 500.0, 10.0, velocityM, 50);

    newspace.populateCells(particleDistribution);
    newspace.populateCells(particleDistributionM);

    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setBackgroundBrush(QBrush(Qt::white));

    QGraphicsView view(&scene);
    view.show();
    view.resize(1200, 800);
    QList<QGraphicsEllipseItem *> particleItems;
    QList<QGraphicsLineItem *> lineItems;
    QTimer timer;
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();

    QObject::connect(&timer, &QTimer::timeout, [&]()
                     {

    // Remove old particle items from the scene
    for (auto item : particleItems) {
        scene.removeItem(item);
        delete item;
    }
    particleItems.clear();

    //     for (auto item : lineItems) {
    //     scene.removeItem(item);
    //     delete item;
    // }
    // lineItems.clear(); 

    // for (int x = 0; x < view.width(); x += gridSize) {
    //     QGraphicsLineItem *line = scene.addLine(x, 0, x, view.height());
    //     lineItems.append(line);
    // }
    // for (int y = 0; y < view.height(); y += gridSize) {
    //     QGraphicsLineItem *line = scene.addLine(0, y, view.width(), y);
    //     lineItems.append(line);
    // }

    newspace.updateCells(timeStep);
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
