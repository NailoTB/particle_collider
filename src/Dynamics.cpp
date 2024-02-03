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
    double dotProduct(const std::vector<double> &vector1, const std::vector<double> &vector2)
    {
        double product = 0.0;
        for (int i = 0; i < vector1.size(); i++)
        {
            product += vector1[i] * vector2[i];
        }
        return product;
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

        std::vector<double> vectorFrom1To2 = {pos1[0] - pos2[0], pos1[1] - pos2[1], pos1[2] - pos2[2]};
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
        double m1 = fermion1->getMass();
        double m2 = fermion2->getMass();

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

        double v1t = dotProduct(velocity1, momentumTransferTangent);
        double v2t = dotProduct(velocity2, momentumTransferTangent);
        double v1n = dotProduct(velocity1, momentumTransferDirection);
        double v2n = dotProduct(velocity2, momentumTransferDirection);

        double collisionForce = 1.0 / (1.0 + std::pow(distance, 2));
        double inertiaFactor = 1.0 - collisionForce;
        //collisionForce = 1.0;
        double v1nNew = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
        double v2nNew =  (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

        std::vector<double> newVelocityOne(3, 0.0), newVelocityTwo(3, 0.0);
        for (int i = 0; i < 3; i++)
        {
            newVelocityOne[i] = collisionForce*(v1nNew*momentumTransferDirection[i] + v1t*momentumTransferTangent[i]);
            newVelocityTwo[i] = collisionForce*(v2nNew*momentumTransferDirection[i] + v2t*momentumTransferTangent[i]);
            newVelocityOne[i] += inertiaFactor*velocity1[i];
            newVelocityTwo[i] += inertiaFactor*velocity2[i];


        }
        fermion1->setVelocity(newVelocityOne);
        fermion2->setVelocity(newVelocityTwo);
    }
}
