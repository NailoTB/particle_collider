// Particle.cpp

#include "Particle.h"
#include <cmath>
#include "Dynamics.h"
#include "Constants.h"

Particle::Particle(const std::string &name, const double mass, const double charge,
                   const std::vector<double> &position, const std::vector<double> &velocity)
    : name(name), mass(mass), charge(charge), position(position), velocity(velocity)
{
    updateFourMomentum();
}

void Particle::updateFourMomentum()
{
    double gammaFactor = Dynamics::gamma(Particle::velocity);
    double gammaMass = gammaFactor * mass;

    std::vector<double> threeMomentum = {gammaMass * velocity[0], gammaMass * velocity[1], gammaMass * velocity[2]};
    double velocitySquare = std::pow(Dynamics::velocityNorm(threeMomentum), 2);
    double energy_updated = std::sqrt(velocitySquare * std::pow(speedOfLight, 2) + mass * mass * std::pow(speedOfLight, 4));

    energy = energy_updated;
    fourMomentum = {energy_updated / speedOfLight, threeMomentum[0], threeMomentum[1], threeMomentum[2]};
}

void Particle::addFourMomentum(const std::vector<double>& addedMomentum){
    for (int i = 0; i < addedMomentum.size() ; i++){
        fourMomentum[i] = fourMomentum[i] + addedMomentum[i];
    }
}


void Particle::updateVelocity()
{
    double scaleFactor = std::pow(speedOfLight,2)/energy;
    velocity = {fourMomentum[1] * scaleFactor, fourMomentum[2] * scaleFactor, fourMomentum[3] * scaleFactor};
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
const std::vector<double> &Particle::getFourMomentum() const
{
    return fourMomentum;
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