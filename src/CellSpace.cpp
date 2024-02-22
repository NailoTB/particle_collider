// CellSpace.cpp

#include "CellSpace.h"

CellSpace::CellSpace(unsigned int columns, unsigned int rows, double cellSize) : rows(rows), columns(columns), cellSize(cellSize)
{
    createGrid();
}

void CellSpace::createGrid()
{
    std::vector<std::vector<Cell>> cellGrid;
    double xcoord = 0.0;
    double ycoord = 0.0;

    for (unsigned int rindex = 0; rindex < rows; rindex++)
    {
        xcoord = 0.0;
        std::vector<Cell> cellRow;
        for (unsigned int cindex = 0; cindex < columns; cindex++)
        {
            Cell newcell = Cell(xcoord, ycoord, cellSize);
            cellRow.push_back(std::move(newcell));
            xcoord += cellSize;
        }
        cellGrid.push_back(std::move(cellRow));
        ycoord += cellSize;
    }
    grid = std::move(cellGrid);
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

void CellSpace::populateCells(std::vector<std::unique_ptr<Particle>> &particleVector)
{
    for (auto &particle : particleVector)
    {
        auto particlePos = particle->getPosition();

        int xCell = std::floor(particlePos[0] / cellSize);
        int yCell = std::floor(particlePos[1] / cellSize);

        if (xCell >= columns || yCell >= rows)
        {
            continue;
        }
        grid[yCell][xCell].addParticle(particle);
    }
}

std::vector<std::vector<double>> CellSpace::allParticlePositions()
{
    std::vector<std::vector<double>> allParticlePositions;
    for (auto &cellRow : grid)
    {
        for (auto &cell : cellRow)
        {
            auto particlePositionsInCell = cell.particlePositions();
            allParticlePositions.insert(allParticlePositions.end(), particlePositionsInCell.begin(), particlePositionsInCell.end());
        }
    }

    return allParticlePositions;
};

void CellSpace::checkNeighborCollision(Cell &cell1, Cell &cell2)
{
    auto &particlesInCellOne = cell1.particles;
    auto &particlesInCellTwo = cell2.particles;

    for (auto &particle1 : particlesInCellOne)
    {
        for (auto &particle2 : particlesInCellTwo)
        {
            if (Dynamics::interactFermionFermion(particle1, particle2))
            {
                Dynamics::collision(particle1, particle2);
            }
        }
    }
}

void CellSpace::updateCells(double dt)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            grid[i][j].checkCollisions();
            if (j + 1 < columns)
            {
                checkNeighborCollision(grid[i][j], grid[i][j + 1]);
            }
            if (i + 1 < rows)
            {
                checkNeighborCollision(grid[i][j], grid[i + 1][j]);
            }
            if (i + 1 < rows && j + 1 < columns)
            {
                checkNeighborCollision(grid[i][j], grid[i + 1][j + 1]);
            }
            grid[i][j].update(dt);
        }
    }

    std::vector<std::tuple<std::unique_ptr<Particle>, int, int, int, int>> moves;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            auto &outOfBoundsStructure = grid[i][j].outOfBoundsParticles;
            if (!outOfBoundsStructure.empty())
            {
                for (auto &outOfBounds : outOfBoundsStructure)
                {
                    auto &particlePtr = std::get<0>(outOfBounds);
                    auto &newCell = std::get<1>(outOfBounds);

                    moves.push_back(std::make_tuple(std::move(particlePtr), i, j, std::get<0>(newCell), std::get<1>(newCell)));
                }
            }
        }
    }

    for (auto &move : moves)
    {
        auto &particle = std::get<0>(move);
        int oldRow = std::get<1>(move), oldCol = std::get<2>(move);
        int newRow = std::get<3>(move), newCol = std::get<4>(move);

        if (newRow == 0 || newCol == 0 || newRow == rows - 1 || newCol == columns - 1)
        {
            grid[newRow][newCol].addParticle(particle);
            grid[newRow][newCol].clear();
        }
        else
        {
            grid[newRow][newCol].addParticle(particle);
        }
        grid[oldRow][oldCol].removeParticle(particle);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            grid[i][j].outOfBoundsParticles.clear();
        }
    }
}
