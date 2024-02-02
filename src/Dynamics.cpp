// Dynamics.cpp

#include "Dynamics.h"

namespace Dynamics
{
    std::vector<std::unique_ptr<Particle>> generateParticleDistribution(double xCentre, double yCentre, double spread, std::vector<double> velocity, int numParticles)
    {
        // TODO: Make more general for different particles and velocities
        std::random_device rd;
        std::mt19937 generator(rd());

        std::normal_distribution<double> xDistribution(xCentre, spread);
        std::normal_distribution<double> yDistribution(yCentre, spread);
        std::normal_distribution<double> vDistribution(velocity[0], 1);

        std::vector<std::unique_ptr<Particle>> generatedParticles;

        for (unsigned int i = 0; i < numParticles; i++)
        {
            double velocityFactor = vDistribution(generator);
            std::vector<double> velocityNoised = {velocity[0] + velocityFactor, velocity[1], 0.0};

            std::vector<double> particle_position = {xDistribution(generator), yDistribution(generator), 0};
            std::unique_ptr<Fermion> newParticle = std::make_unique<Fermion>("Electron", electronMass, -eCharge, particle_position, velocityNoised);
            generatedParticles.push_back(std::move(newParticle));
        }
        return generatedParticles;
    }

    void updatePosition(std::unique_ptr<Particle> &particle, const double dt)
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
        // Remove Photon
    }

    double exponential(double x)
    {
        return std::exp(-interactionLength * x);
    }

    double particleDistance(std::unique_ptr<Particle> &particle1, std::unique_ptr<Particle> &particle2)
    {
        auto directionVector = particleDirectionVector(particle1, particle2);
        double distance = 0.0;
        for (int i = 0; i < directionVector.size(); i++)
        {
            distance += std::pow(directionVector[i], 2);
        }
        return std::sqrt(distance);
    }

    std::vector<double> particleDirectionVector(std::unique_ptr<Particle> &particle1, std::unique_ptr<Particle> &particle2)
    {
        auto pos1 = particle1->getPosition();
        auto pos2 = particle2->getPosition();

        std::vector<double> vectorFrom1To2 = {pos2[0] - pos1[0], pos2[1] - pos1[1], pos2[2] - pos1[2]};
        return vectorFrom1To2;
    }
    bool interactFermionFermion(std::unique_ptr<Particle> &fermion1, std::unique_ptr<Particle> &fermion2)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<double> propability(0, 1.0);

        double distance = particleDistance(fermion1, fermion2);
        return exponential(distance) >= propability(generator);
    }

    void collision(std::unique_ptr<Particle> &fermion1, std::unique_ptr<Particle> &fermion2)
    {
        double distance = particleDistance(fermion1, fermion2);
        double collisionForce = 1 / (1.0 + std::pow(distance, 2));

        std::vector<double> direction = particleDirectionVector(fermion1, fermion2);
        std::vector<double> momentumTransfer{0, 0};
        momentumTransfer[0] = direction[0] / distance;
        momentumTransfer[1] = direction[1] / distance;

        auto velocity1 = fermion1->getVelocity();
        auto velocity2 = fermion2->getVelocity();

        std::vector<double> relativeVelocity = {velocity2[0] - velocity1[0], velocity2[1] - velocity1[1]};
        double impulseMagnitude = collisionForce * (relativeVelocity[0] * momentumTransfer[0] + relativeVelocity[1] * momentumTransfer[1]);
        std::vector<double> impulse = {impulseMagnitude * momentumTransfer[0], impulseMagnitude * momentumTransfer[1]};
        // TODO: Mass Dependance
        for (int i = 0; i < 2; i++)
        {
            velocity1[i] += impulse[i];
            velocity2[i] -= impulse[i];
        }
        fermion1->setVelocity(velocity1);
        fermion2->setVelocity(velocity2);
    }
}
