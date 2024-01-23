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
    for (auto& particle : particles)
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

// void Cell::checkCollisions()
//{
//  Implement collision detection between particles within this cell
//}

// Other cell-related methods
