// Dynamics.cpp

#include "Dynamics.h"

void Dynamics::updatePosition(Particle& particle, const double dt) {

    const std::vector<double>& velocity = particle.getVelocity();
    const std::vector<double>& currentPosition = particle.getPosition();

    std::vector<double> newPosition(currentPosition.size());

    for( int i = 0 ; i < velocity.size() ; i++ ) {
        newPosition[i] = currentPosition[i] + velocity[i] * dt;
    }

    particle.setPosition(newPosition);
}

void Dynamics::updateVelocity(Particle& particle, const std::vector<double>& newVelocity) {
    particle.setVelocity(newVelocity);
}
// Implement other physics-related functions here
