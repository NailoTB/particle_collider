// Cell.cpp

#include "Cell.h"

Cell::Cell(double x, double y, double size) : x_coordinate(x), y_coordinate(y), size(size)
{
}

void Cell::addParticle(const Particle *particle)
{
    particles.push_back(particle);
}

void Cell::removeParticle(const Particle *particle)
{
    auto newEnd = std::remove(particles.begin(), particles.end(), particle);
    particles.erase(newEnd, particles.end());
}

double Cell::returnXCoordinate(){
    return(x_coordinate);
}


//void Cell::checkCollisions()
//{
    // Implement collision detection between particles within this cell
//}

// Other cell-related methods
