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
    double xLength = 1400;
    double yLength = 800;
    double gridSize = 10;
    
    CellSpace newspace(int(xLength/gridSize), int(yLength/gridSize), gridSize);
    std::vector<double> velocityP = {70.0, 0.0, 0.0};
    std::vector<double> velocityM = {-70.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Particle>> particleDistribution = Dynamics::generateInitialParticleDistribution(200.0, 400.0, 20.0, velocityP, 200);
    std::vector<std::unique_ptr<Particle>> particleDistributionM = Dynamics::generateInitialParticleDistribution(1200.0, 400.0, 20.0, velocityM, 200);

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
