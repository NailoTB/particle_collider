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
    void populateCells(std::vector<std::shared_ptr<Particle>> &);
    void updateCells(double);

private:
    unsigned int rows;
    unsigned int columns;
    double cellSize;
    void createGrid();
    void clearCells();
};

#endif // CELLSPACE_H
