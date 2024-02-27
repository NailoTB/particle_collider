// Dynamics.h

#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "Particle.h"
#include "Fermion.h"
#include "Boson.h"
#include "Constants.h"
#include "VectorMath.h"
#include <cmath>
#include <random>
#include <memory>

namespace Dynamics
{
    std::vector<std::unique_ptr<Particle>> generateInitialParticleDistribution(double, double, double, std::vector<double>, int);
    std::vector<std::unique_ptr<Particle>> generateParticleDistribution(double, double, double, std::vector<double>, int);
    double coulombInteraction(double&, double&, double&);
    void updatePosition(std::unique_ptr<Particle>& particle, const double dt);
    bool interactFermionFermion(std::unique_ptr<Particle> &, std::unique_ptr<Particle> &);
    void collision(std::unique_ptr<Particle> &, std::unique_ptr<Particle> &);
    std::vector<double> particleDirectionVector(std::unique_ptr<Particle> &, std::unique_ptr<Particle> &);
    double particleDistance(std::unique_ptr<Particle> &, std::unique_ptr<Particle> &);
}

#endif // DYNAMICS_H
