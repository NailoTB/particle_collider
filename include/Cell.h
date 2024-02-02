// Cell.h

#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <tuple>
#include "Particle.h"
#include "Dynamics.h"
class Cell
{
public:
    Cell(double x, double y, double size);
    void addParticle(std::unique_ptr<Particle> &particle);
    void removeParticle(const std::unique_ptr<Particle> &particle);

    void clear();
    void printParticleList();
    void checkCollisions();
    std::vector<std::vector<double>> particlePositions();
    void update(double);
    double x_coordinate;
    double y_coordinate;
    double size; // In the future maybe not constant
    std::vector<std::tuple<std::unique_ptr<Particle>, std::tuple<int, int>>> outOfBoundsParticles;
    std::vector<std::unique_ptr<Particle>> particles;
private:
    
    std::tuple<int, int> isOutOfBounds(std::unique_ptr<Particle> &, int, int);
};

#endif // CELL_H
