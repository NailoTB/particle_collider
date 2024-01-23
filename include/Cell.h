// Cell.h

#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "Particle.h"

class Cell
{
public:
    Cell(double x, double y, double size);
    void addParticle(std::shared_ptr<Particle> particle);
    void removeParticle(std::shared_ptr<Particle> particle);
    void clear();
    void printParticleList();
    double x_coordinate;
    double y_coordinate;
    double size; // In the future maybe not constant
private:
    std::vector<std::shared_ptr<Particle>> particles;
};

#endif // CELL_H
