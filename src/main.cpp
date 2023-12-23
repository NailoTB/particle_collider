#include "Particle.h"
#include "Dynamics.h"
#include <iostream>

int main() {
    // Create a particle
    Particle myParticle("Proton", 1.0, 1.0, {0.0, 0.0, 0.0}, {1.0, 2.0, -3.0});

    // Simulate movement for ten time steps
    const double dt = 0.1;  // Time increment
    for (int step = 1; step <= 10; ++step) {
        Dynamics::updatePosition(myParticle, dt);
        std::cout << "Time Step " << step << ": Position = (";
        
        const std::vector<double>& position = myParticle.getPosition();
        for (std::size_t i = 0; i < position.size(); ++i) {
            std::cout << position[i];
            if (i < position.size() - 1) {
                std::cout << ", ";
            }
        }
        
        std::cout << ")\n";
    }

    return 0;
}