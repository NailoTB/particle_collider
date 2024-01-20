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
    Cell(double x, double y, double size);
    void addParticle(const Particle *particle);
    void removeParticle(const Particle *particle);
    double returnXCoordinate();
    double x_coordinate; 
    double y_coordinate;
    double size; // In the future maybe not constant
private:
    std::vector<const Particle*> particles;
};

// Cell* createCell(const double x, const double y, const double size){
    // Cell* newCell = &Cell(x, y, size);
    // return(newCell);
// }

#endif // CELL_H
