// CellSpace.h

#ifndef CELLSPACE_H
#define CELLSPACE_H

#include <string>
#include <vector>
#include <cmath>
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
    void populateCells(const std::vector<Particle *> &, bool );
    void clearCells();
};

#endif // CELLSPACE_H
