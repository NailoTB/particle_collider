#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>
#include <vector>

class Particle {
public:
    // Constructors and Destructor
    Particle(const std::string& name, const double mass, const double charge, 
    const std::vector<double>& position, const std::vector<double>& velocity);

    ~Particle();

    std::string getName() const;
    double getMass() const;
    double getCharge() const;

    const std::vector<double>& getPosition() const;
    const std::vector<double>& getVelocity() const;
    const std::vector<double>& getFourMomentum() const;

    void setName(const std::string& name);
    void setPosition(const std::vector<double>& position);
    void setVelocity(const std::vector<double>& velocity);

    void updateVelocity();
    void addFourMomentum(const std::vector<double>& addedMomentum);
    virtual void updateFourMomentum();

protected:
    std::string name;
    const double mass;
    const double charge;
    double energy;
    std::vector<double> position;
    std::vector<double> velocity;
    std::vector<double> fourMomentum;
};

#endif // PARTICLE_H
