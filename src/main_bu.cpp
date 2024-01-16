#include "Particle.h"
#include "Boson.h"
#include "Fermion.h"
#include "Dynamics.h"
#include <iostream>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QLabel>

int main(int argc, char **argv)
{
    // Create a particle
    Boson photon("Photon", 0.0, -1.0, 100.0, {1.0, 0.0, 0.0}, {0.5*speedOfLight, std::sqrt(3)/2*speedOfLight, 0.0});
    Fermion electron("Electron", electronMass, -eCharge, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0});

    // Simulate movement for ten time steps
    const double dt = 0.1; // Time increment
    for (int step = 1; step <= 20; ++step)
    {
        //Dynamics::updatePosition(photon, dt);
        Dynamics::updatePosition(electron, dt);

        std::cout << "Time Step " << step << ": Position = (";

        const std::vector<double> &elect_position = electron.getPosition();
        for (std::size_t i = 0; i < elect_position.size(); ++i)
        {
            std::cout << elect_position[i];
            if (i < elect_position.size() - 1)
            {
                std::cout << ", ";
            }
        }

        if (step == 2)
        {
            Dynamics::interactPhotonFermion(photon, electron);
            std::cout << "Photon 4mom: " << photon.getFourMomentum()[2] << std::endl;
            std::cout << "Electron new velocity: ";
            const std::vector<double> &newVel = electron.getVelocity();
            for (std::size_t i = 0; i < newVel.size(); ++i)
            {
                std::cout << newVel[i];
                if (i < newVel.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << ")\n";
        }

        std::cout << ")\n";
    }

    return 0;
}