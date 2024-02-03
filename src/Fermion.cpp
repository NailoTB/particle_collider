// Fermion.cpp

#include "Fermion.h"

Fermion::Fermion(const std::string& name, double mass, double charge,
        const std::vector<double>& position, const std::vector<double>& velocity)
    : Particle(name, mass, charge, position, velocity) 
{
}