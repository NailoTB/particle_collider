// Dynamics.cpp

#include "Dynamics.h"

namespace Dynamics
{

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> propability(0, 1.0);

    std::vector<std::unique_ptr<Particle>> generateInitialParticleDistribution(double xCentre, double yCentre, double spread, std::vector<double> velocity, int numParticles)
    {
        // TODO: Make more general for different particles and velocities
        std::normal_distribution<double> xDistribution(xCentre, spread);
        std::normal_distribution<double> yDistribution(yCentre, spread);
        std::normal_distribution<double> vDistribution(velocity[0], 1);

        std::vector<std::unique_ptr<Particle>> generatedParticles;

        for (unsigned int i = 0; i < numParticles; i++)
        {
            double velocityFactor = vDistribution(generator);
            std::vector<double> velocityNoised = {velocity[0] + velocityFactor, velocity[1], 0.0};

            std::vector<double> particlePosition = {xDistribution(generator), yDistribution(generator), 0};
            std::unique_ptr<Fermion> newParticle = std::make_unique<Fermion>("Electron", electronMass, -eCharge, particlePosition, velocityNoised);
            generatedParticles.push_back(std::move(newParticle));
        }
        return generatedParticles;
    }

    std::vector<std::unique_ptr<Particle>> generateParticleDistribution(double xCentre, double yCentre, double spread, double mass, std::vector<double> velocity, int numParticles)
    {
        // TODO: Make more general for different particles and velocities
        std::normal_distribution<double> xDistribution(xCentre, spread);
        std::normal_distribution<double> yDistribution(yCentre, spread);

        std::vector<std::unique_ptr<Particle>> generatedParticles;

        for (unsigned int i = 0; i < numParticles; i++)
        {
            std::vector<double> particlePosition = {xDistribution(generator), yDistribution(generator), 0};
            std::unique_ptr<Fermion> newParticle = std::make_unique<Fermion>("Electron", mass, -eCharge, particlePosition, velocity);
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

        for (size_t i = 0; i < currentPosition.size(); i++)
        {

            newPosition[i] = currentPosition[i] + velocity[i] * dt;
        }

        particle->setPosition(newPosition);
    }

    double coulombInteraction(double &separation, double &charge1, double &charge2){
        double chargeFactor = charge1 * charge2;
        return chargeFactor / (chargeFactor + 2*std::pow(separation, 2));
    }

    double particleDistance(std::unique_ptr<Particle> &particle1, std::unique_ptr<Particle> &particle2)
    {
        auto directionVector = particleDirectionVector(particle1, particle2);
        return VectorMath::norm(directionVector);
    }

    std::vector<double> particleDirectionVector(std::unique_ptr<Particle> &particle1, std::unique_ptr<Particle> &particle2)
    {
        auto pos1 = particle1->getPosition();
        auto pos2 = particle2->getPosition();

        return VectorMath::subtraction(pos1, pos2);
    }
    bool interactFermionFermion(std::unique_ptr<Particle> &fermion1, std::unique_ptr<Particle> &fermion2)
    {
        double distance = particleDistance(fermion1, fermion2);
        double charge1 = fermion1->getCharge();
        double charge2 = fermion2->getCharge();
        return coulombInteraction(distance, charge1, charge2) >= propability(generator);
    }

    void collision(std::unique_ptr<Particle> &fermion1, std::unique_ptr<Particle> &fermion2)
    {
        // TODO: Refactor this function
        double distance = particleDistance(fermion1, fermion2);
        double m1 = fermion1->getMass();
        double m2 = fermion2->getMass();
        double charge1 = fermion1->getCharge();
        double charge2 = fermion2->getCharge();

        std::vector<double> direction = particleDirectionVector(fermion1, fermion2);

        std::vector<double> momentumTransferDirection(3, 0.0);
        std::vector<double> momentumTransferTangent(3, 0.0);

        momentumTransferDirection[0] = direction[0] / distance;
        momentumTransferDirection[1] = direction[1] / distance;
        momentumTransferDirection[2] = direction[2] / distance;
        momentumTransferTangent[0] = -1.0 * momentumTransferDirection[1];
        momentumTransferTangent[1] = momentumTransferDirection[0];
        momentumTransferTangent[2] = momentumTransferDirection[2];

        auto velocity1 = fermion1->getVelocity();
        auto velocity2 = fermion2->getVelocity();

        double v1t = VectorMath::dotProduct(velocity1, momentumTransferTangent);
        double v2t = VectorMath::dotProduct(velocity2, momentumTransferTangent);
        double v1n = VectorMath::dotProduct(velocity1, momentumTransferDirection);
        double v2n = VectorMath::dotProduct(velocity2, momentumTransferDirection);

        double collisionForce = 1.0 - coulombInteraction(distance, charge1, charge2);
        double inertiaFactor = 1 - collisionForce;

        double v1nNew = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
        double v2nNew = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

        std::vector<double> newVelocityOne(3, 0.0), newVelocityTwo(3, 0.0);
        for (unsigned int i = 0; i < 3; i++)
        {
            newVelocityOne[i] = collisionForce * (v1nNew * momentumTransferDirection[i] + v1t * momentumTransferTangent[i]);
            newVelocityTwo[i] = collisionForce * (v2nNew * momentumTransferDirection[i] + v2t * momentumTransferTangent[i]);
            newVelocityOne[i] += inertiaFactor * velocity1[i];
            newVelocityTwo[i] += inertiaFactor * velocity2[i];
        }
        fermion1->setVelocity(newVelocityOne);
        fermion2->setVelocity(newVelocityTwo);
    }
}
