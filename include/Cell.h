// Cell.h

#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
#include <algorithm>
#include "Particle.h"

class Cell
{
public:
    Cell(const double x, const double y, const double size);
    void addParticle(const Particle *particle);
    void removeParticle(const Particle *particle);
private:
    std::vector<const Particle*> particles;
    const double x_coordinate; 
    const double y_coordinate;
    const double size; // In the future maybe not constant
};

#endif // CELL_H
