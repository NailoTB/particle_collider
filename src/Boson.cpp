// Boson.cpp

#include "Boson.h"
#include "Constants.h"
#include "Dynamics.h"

Boson::Boson(const std::string& name, double mass, double charge, const double frequency,
        const std::vector<double>& position, const std::vector<double>& velocity)
    : Particle(name, mass, charge, position, velocity), frequency(frequency)
{   
    energy = plankConstant * frequency; 
    updateFourMomentum();
}

void Boson::updateFourMomentum() {
    fourMomentum = {energy/speedOfLight, energy*velocity[0]/speedOfLight, energy*velocity[1]/speedOfLight, energy*velocity[2]/speedOfLight};
}