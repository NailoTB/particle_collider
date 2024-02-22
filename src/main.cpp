#include "Particle.h"
#include "Boson.h"
#include "Fermion.h"
#include "Dynamics.h"
#include "CellSpace.h"
#include "qt/SimulationWindow.h"

#include <stdio.h>
#include <memory>
#include <QApplication>

int main(int argc, char **argv)
{
    // TODO: gridSize Dependent on interaction length
    double gridSize = 10;
    int xGridSpan = 140;
    int yGridSpan = 80;
    CellSpace newspace(xGridSpan, yGridSpan, gridSize);
    std::vector<double> velocityP = {70.0, 0.0, 0.0};
    std::vector<double> velocityM = {-70.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Particle>> particleDistribution = Dynamics::generateParticleDistribution(200.0, 500.0, 10.0, velocityP, 50);
    std::vector<std::unique_ptr<Particle>> particleDistributionM = Dynamics::generateParticleDistribution(500.0, 500.0, 10.0, velocityM, 50);

    newspace.populateCells(particleDistribution);
    newspace.populateCells(particleDistributionM);

    QApplication app(argc, argv);
    SimulationWindow *window = new SimulationWindow();
    window->passCellSpaceToScene(&newspace);
    window->show();
    int execResult = app.exec();

    delete window;
    return 0;
}
