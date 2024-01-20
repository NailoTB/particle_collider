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

    CellSpace();

private:
    std::vector<std::vector<Cell>> grid;
};

#endif // CELLSPACE_H
