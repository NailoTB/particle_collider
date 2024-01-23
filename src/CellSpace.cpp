// CellSpace.cpp

#include "CellSpace.h"

CellSpace::CellSpace(unsigned int rows, unsigned int columns, double cellSize) : rows(rows), columns(columns), cellSize(cellSize)
{
    createGrid();
}

void CellSpace::createGrid()
{
    std::vector<std::vector<Cell>> cellGrid;
    double xcoord = 0.0;
    double ycoord = 0.0;
    for (unsigned int rindex = 0; rindex <= rows; rindex++)
    {
        std::vector<Cell> cellRow;
        for (unsigned int cindex = 0; cindex <= columns; cindex++)
        {
            Cell newcell = Cell(xcoord, ycoord, cellSize);
            cellRow.push_back(newcell);
            ycoord += cellSize;
        }
        cellGrid.push_back(cellRow);
        xcoord += cellSize;
    }
    grid = cellGrid;
}

void CellSpace::clearCells()
{
    for (unsigned int rindex = 0; rindex < rows; rindex++)
    {
        for (unsigned int cindex = 0; cindex < columns; cindex++)
        {
            grid[rindex][cindex].clear();
        }
    }
}

void CellSpace::populateCells(std::vector<std::shared_ptr<Particle>> &particleVector, bool clearExistingCells = true)
{
    if (clearExistingCells)
    {
        clearCells();
    }

    for (const auto &particle : particleVector)
    {
        auto particlePos = particle->getPosition();

        int xCell = std::floor(particlePos[0] / cellSize);
        int yCell = std::floor(particlePos[1] / cellSize);

        if (xCell >= columns || yCell >= rows)
        {
            std::cout << "Particle out of grid space" << '\n';
            continue;
        }
        grid[xCell][yCell].addParticle(particle);
    }
}

//TODO: Update Cells
//TODO: Move particles to new Cells
