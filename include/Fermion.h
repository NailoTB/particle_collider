// Fermion.h
#pragma once

#include "Particle.h"

class Fermion : public Particle
{
public:
    Fermion(const std::string &name, double mass, double charge,
            const std::vector<double> &position, const std::vector<double> &velocity);
};