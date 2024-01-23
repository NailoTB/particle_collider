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

void CellSpace::populateCells(std::vector<std::shared_ptr<Particle>> &particleVector)
{
    for (const auto &particle : particleVector)
    {
        auto particlePos = particle->getPosition();

        int xCell = std::floor(particlePos[0] / cellSize);
        int yCell = std::floor(particlePos[1] / cellSize);

        if (xCell >= columns || yCell >= rows)
        {
            // TODO: negative case
            // TODO: Flag particle for deletion
            //std::cout << "Particle out of grid space" << '\n';
            continue;
        }
        grid[xCell][yCell].addParticle(particle);
    }
}

void CellSpace::updateCells(double dt)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            grid[i][j].update(dt);
        }
    }


}
// TODO: Move particles to new Cells
    // returns the direction where particle went over
    // 1, -1 -> x-direction
    // 2, -2 -> y-direction
    // in standard base
        // auto newPos = particle->getPosition();
        // if (newPos[0] > x_coordinate + size)
        // {
        //     return 1;
        // }
        // if (newPos[0] < x_coordinate)
        // {
        //     return -1;
        // }
        // if (newPos[1] > y_coordinate + size)
        // {
        //     return 2;
        // }
        // if (newPos[2] < y_coordinate)
        // {
        //     return -2;
        // }
        // return 0;