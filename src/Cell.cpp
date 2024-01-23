// Cell.cpp

#include "Cell.h"

Cell::Cell(double x, double y, double size) : x_coordinate(x), y_coordinate(y), size(size)
{
}
void Cell::printParticleList()
{
    if (particles.empty())
    {
        std::cout << "Cell is empty" << '\n';
        return;
    }
    int particleCount = 0;
    std::cout << "In Cell at coordinates: " << x_coordinate << " " << y_coordinate << '\n';

    for (auto &particle : particles)
    {
        std::cout << "Particle number " + std::to_string(particleCount) + " at: ";
        std::cout << particle->getPosition()[0] << " " << particle->getPosition()[1] << '\n';
        particleCount++;
    }
}

void Cell::addParticle(std::shared_ptr<Particle> particle)
{
    particles.push_back(particle);
}

void Cell::removeParticle(std::shared_ptr<Particle> particle)
{
    auto newEnd = std::remove(particles.begin(), particles.end(), particle);
    particles.erase(newEnd, particles.end());
}

void Cell::clear()
{
    particles.clear();
}

std::tuple<int, int> Cell::isOutOfBounds(std::shared_ptr<Particle> particle, int selfRow, int selfColumn)
{
    // Returns the index of the new cell
    int newRow = selfRow;
    int newColumn = selfColumn;

    auto newPos = particle->getPosition();
    bool overX, underX, overY, underY;

    overX = (newPos[0] > x_coordinate + size);
    underX = (newPos[0] < x_coordinate);
    overY = (newPos[1] > y_coordinate + size);
    underY = (newPos[1] < y_coordinate);
    if (overX)
    {
        newColumn++;
    }
    if (overY)
    {
        newRow++;
    }
    if (underX)
    {
        newColumn--;
    }
    if (underY)
    {
        newRow--;
    }

    return std::make_tuple(newRow, newColumn);
}

void Cell::update(double dt)
{
    if (particles.empty())
    {
        return;
    }

    int selfRow = int(y_coordinate / size);
    int selfColumn = int(x_coordinate / size);
    for (auto particle : particles)
    {
        Dynamics::updatePosition(particle, dt);
        auto outOfBounds = isOutOfBounds(particle, selfRow, selfColumn);

        if (std::get<0>(outOfBounds) != selfRow || std::get<1>(outOfBounds) != selfColumn)
        {
            outOfBoundsParticles.push_back(std::make_tuple(particle, outOfBounds));
        }
    }

    // TODO: Include collisions
}

// void Cell::checkCollisions()
//{
//  Implement collision detection between particles within this cell
//}

// Other cell-related methods
