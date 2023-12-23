#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>
#include <vector>

class Particle {
public:
    // Constructors and Destructor
    Particle();

    Particle(const std::string& name, const double mass, const double charge, 
    const std::vector<double>& position, const std::vector<double>& velocity);

    ~Particle();

    std::string getName() const;
    double getMass() const;
    double getCharge() const;

    const std::vector<double>& getPosition() const;
    const std::vector<double>& getVelocity() const;

    void setName(const std::string& name);
    void setPosition(const std::vector<double>& position);
    void setVelocity(const std::vector<double>& velocity);

private:
    // Private member variables
    std::string name;
    const double mass;
    const double charge;
    std::vector<double> position;
    std::vector<double> velocity;
};

#endif // PARTICLE_H
