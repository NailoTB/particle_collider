// CellSpace.cpp

#include "CellSpace.h"
// #include "Cell.h"

CellSpace::CellSpace(unsigned int rows, unsigned int columns, double cellSize) : rows(rows), columns(columns), cellSize(cellSize)
{
    createGrid();
}

void CellSpace::createGrid(){
    // std::Vector<std::Vector<Cell>>[rows][columns] cellGrid;
    std::vector<std::vector<Cell>> cellGrid;//(rows,std::vector<Cell*> (columns));
    double xcoord =  0.0;
    double ycoord = 0.0;
    for (unsigned int rindex=0; rindex<=rows; rindex++){
        std::vector<Cell> cellRow;
        for (unsigned int cindex=0; cindex<=columns; cindex++){
            Cell newcell = Cell(xcoord, ycoord, cellSize);
            cellRow.push_back(newcell);
            ycoord += cellSize;
        }
        cellGrid.push_back(cellRow);
        xcoord += cellSize;
    }
    grid = cellGrid;
}

// void CellSpace::addParticleToCell(int x, int y, const Particle &particle)
// {
// }

// void update()
// {
// }
