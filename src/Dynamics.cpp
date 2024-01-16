// Dynamics.cpp

#include "Dynamics.h"

namespace Dynamics
{
    void updatePosition(Particle &particle, const double dt)
    {

        const std::vector<double> &velocity = particle.getVelocity();
        const std::vector<double> &currentPosition = particle.getPosition();
        const double &mass = particle.getMass();
        std::vector<double> newPosition(currentPosition.size());

        for (int i = 0; i < currentPosition.size(); i++)
        {

            newPosition[i] = currentPosition[i] + velocity[i] * dt;
        }

        particle.setPosition(newPosition);
    }

    double velocityNorm(const std::vector<double> &velocityVector)
    {
        double velocity = 0.0;
        for (double v_i : velocityVector)
        {
            velocity += v_i * v_i;
        }
        return std::sqrt(velocity);
    }

    double gamma(const std::vector<double> &threeVelocity)
    {
        double velocity = velocityNorm(threeVelocity);
        return 1 / std::sqrt(1 - velocity * velocity / (speedOfLight * speedOfLight));
    }

    void interactPhotonFermion(Boson &photon, Fermion &fermion)
    {
        double pseudoCharge = photon.getCharge();
        double fermionCharge = fermion.getCharge();
        double pullPushFactor = 1.0;

        if(pseudoCharge * fermionCharge < 0.0){
            pullPushFactor = -1.0;
        }

        std::vector<double> additionMomentum = photon.getFourMomentum();
        for (int i = 1 ; i < additionMomentum.size(); i++) {
            additionMomentum[i] = pullPushFactor * additionMomentum[i];
        }
        fermion.addFourMomentum(additionMomentum);
        fermion.updateVelocity();
    }

}
