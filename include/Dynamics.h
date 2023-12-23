// Dynamics.h

#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "Particle.h"

class Dynamics {
public:
    static void updatePosition(Particle& particle, const double dt);
    static void updateVelocity(Particle& particle, const std::vector<double>& newVelocity);
};

#endif // DYNAMICS_H
