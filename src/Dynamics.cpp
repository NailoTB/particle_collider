// Dynamics.cpp

#include "Dynamics.h"

namespace Dynamics
{
    std::vector<std::shared_ptr<Particle>> generateParticleDistribution(double xCentre, double yCentre, double spread, std::vector<double> velocity, int numParticles)
    {
        // TODO: Make more general for different particles and velocities
        std::random_device rd;
        std::mt19937 generator(rd());

        std::normal_distribution<double> xDistribution(xCentre, spread);
        std::normal_distribution<double> yDistribution(yCentre, spread);
        std::normal_distribution<double> vDistribution(velocity[0], 1);


        std::vector<std::shared_ptr<Particle>> generatedParticles;

        for (unsigned int i = 0; i < numParticles; i++)
        {
            double velocityFactor = vDistribution(generator);
            std::vector<double> velocityNoised = {velocity[0] + velocityFactor, velocity[1] + velocityFactor, 0.0};

            //std::cout << xDistribution(generator) << std::endl;
            std::vector<double> particle_position = {xDistribution(generator), yDistribution(generator), 0};
            std::shared_ptr<Fermion> newParticle = std::make_shared<Fermion>("Electron", electronMass, -eCharge, particle_position, velocityNoised);
            generatedParticles.push_back(newParticle);
        }
        return generatedParticles;
    }

    void updatePosition(std::shared_ptr<Particle> particle, const double dt)
    {

        const std::vector<double> &velocity = particle->getVelocity();
        const std::vector<double> &currentPosition = particle->getPosition();
        const double &mass = particle->getMass();
        std::vector<double> newPosition(currentPosition.size());

        for (int i = 0; i < currentPosition.size(); i++)
        {

            newPosition[i] = currentPosition[i] + velocity[i] * dt;
        }

        particle->setPosition(newPosition);
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

        if (pseudoCharge * fermionCharge < 0.0)
        {
            pullPushFactor = -1.0;
        }

        std::vector<double> additionMomentum = photon.getFourMomentum();
        for (int i = 1; i < additionMomentum.size(); i++)
        {
            additionMomentum[i] = pullPushFactor * additionMomentum[i];
        }
        fermion.addFourMomentum(additionMomentum);
        fermion.updateVelocity();
    }

}
