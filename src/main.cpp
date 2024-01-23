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

    CellSpace newspace(1, 1, 100000);
    std::vector<double> velocity = {10, 10, 0.0};
    std::vector<std::shared_ptr<Particle>> particleDistribution = Dynamics::generateParticleDistribution(100, 100, 10, velocity, 10);

    newspace.populateCells(particleDistribution);

    QApplication app(argc, argv);

    // Create a QGraphicsScene and a QGraphicsView
    QGraphicsScene scene;
    scene.setBackgroundBrush(QBrush(Qt::white));

    QGraphicsView view(&scene);
    view.show();
    view.resize(800, 600); // Create QGraphicsEllipseItems to represent the particles
    std::vector<QGraphicsEllipseItem*> particleGraphicsItems;
    for (auto particle : particleDistribution){
        QGraphicsEllipseItem *particleItem = new QGraphicsEllipseItem(particle->getPosition()[0], particle->getPosition()[1], 3, 3);
        particleItem->setBrush(QBrush(Qt::blue)); 
        scene.addItem(particleItem);

        particleGraphicsItems.push_back(particleItem);
    }

    std::vector<double> zeroVel = {10, 10, 0.0};
    std::vector<double> zeroPos = {100, 100, 0.0};
    // std::shared_ptr<Fermion> newParticle = std::make_shared<Fermion>("Electron Centre", electronMass, -eCharge, zeroPos, zeroVel);
    // QGraphicsEllipseItem *centreParticle = new QGraphicsEllipseItem(newParticle->getPosition()[0], newParticle->getPosition()[1], 4, 4);
    // centreParticle->setBrush(QBrush(Qt::red)); 
    // scene.addItem(centreParticle);

    const double dt = 0.01; // Time increment
    QTimer timer;
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();
    QObject::connect(&timer, &QTimer::timeout, [&]()
                     {
    newspace.updateCells(dt);
        //Update the positions of QGraphicsEllipseItems
    int itemEnum = 0;
    for (auto particle : particleDistribution){
        particleGraphicsItems[itemEnum]->setPos(particle->getPosition()[0], particle->getPosition()[1]);
        itemEnum++;
    }

    //view.setSceneRect(centreParticle->pos().x() - view.viewport()->width()/2,
    //centreParticle->pos().y() - view.viewport()->height()/2,
    //view.viewport()->width(),
    //view.viewport()->height());
    view.viewport()->update(); });

    timer.start(10);

    return app.exec();
}
