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
    void clearCells();

private:
    std::vector<std::vector<Cell>> grid;
    void checkNeighborCollision(Cell&, Cell&);
    unsigned int rows;
    unsigned int columns;
    double cellSize;
    void createGrid();
};

#endif // CELLSPACE_H
