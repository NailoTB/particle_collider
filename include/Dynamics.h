// Dynamics.h

#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "Particle.h"
#include "Fermion.h"
#include "Boson.h"
#include "Constants.h"
#include <cmath>
#include <random>
#include <memory>
namespace Dynamics
{

    double velocityNorm(const std::vector<double> &threeVelocity);
    double gamma(const std::vector<double> &threeVelocity);
    std::vector<std::shared_ptr<Particle>> generateParticleDistribution(double, double, double, std::vector<double>, int);

    void updatePosition(Particle &particle, const double dt);
    void interactPhotonFermion(Boson& photon, Fermion& fermion);

    //Boson interactFermionFermion(Fermion& fermion1, Fermion& fermion2){
            //read charges
            //generate boson
    //};
}

#endif // DYNAMICS_H
