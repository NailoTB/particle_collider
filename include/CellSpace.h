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
    std::vector<std::vector<double>> allParticlePositions();
    void populateCells(std::vector<std::unique_ptr<Particle>> &);
    void updateCells(double);

private:
    std::vector<std::vector<Cell>> grid;

    unsigned int rows;
    unsigned int columns;
    double cellSize;
    void createGrid();
    void clearCells();
};

#endif // CELLSPACE_H
