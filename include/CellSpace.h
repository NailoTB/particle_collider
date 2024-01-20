// CellSpace.h

#ifndef CELLSPACE_H
#define CELLSPACE_H

#include <string>
#include <vector>
#include "Cell.h"
#include "Particle.h"

class CellSpace
{
public:

    CellSpace(unsigned int, unsigned int, double);
    std::vector<std::vector<Cell>> grid;

private:
    unsigned int rows;
    unsigned int columns;
    double cellSize;
    void createGrid();
};

#endif // CELLSPACE_H
