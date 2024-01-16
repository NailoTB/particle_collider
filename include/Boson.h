// Boson.h
#pragma once

#include "Particle.h"

class Boson : public Particle {
public:
    Boson(const std::string& name, double mass, double charge, const double frequency,
            const std::vector<double>& position, const std::vector<double>& velocity);

    void updateFourMomentum() override;

private:
    const double frequency;
};