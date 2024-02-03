// Particle.cpp

#include "Particle.h"
#include <cmath>
#include "Dynamics.h"
#include "Constants.h"

Particle::Particle(const std::string &name, const double mass, const double charge,
                   const std::vector<double> &position, const std::vector<double> &velocity)
    : name(name), mass(mass), charge(charge), position(position), velocity(velocity)
{
}

Particle::~Particle()
{
    // Cleanup or release resources, if needed
}

std::string Particle::getName() const
{
    return name;
}

double Particle::getMass() const
{
    return mass;
}

double Particle::getCharge() const
{
    return charge;
}

const std::vector<double> &Particle::getPosition() const
{
    return position;
}

const std::vector<double> &Particle::getVelocity() const
{
    return velocity;
}

void Particle::setName(const std::string &newName)
{
    name = newName;
}

void Particle::setPosition(const std::vector<double> &newPosition)
{
    position = newPosition;
}

void Particle::setVelocity(const std::vector<double> &newVelocity)
{
    velocity = newVelocity;
}