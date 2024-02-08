// Cell.cpp

#include "Cell.h"

Cell::Cell(const double x, const double y, double size) : x_coordinate(x), y_coordinate(y), size(size)
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

void Cell::addParticle(std::unique_ptr<Particle> &particle)
{
    particles.push_back(std::move(particle));
}

void Cell::removeParticle(const std::unique_ptr<Particle> &particle)
{
    auto newEnd = std::remove(particles.begin(), particles.end(), particle);
    particles.erase(newEnd, particles.end());
}

void Cell::clear()
{
    particles.clear();
    outOfBoundsParticles.clear();
}

std::tuple<int, int> Cell::isOutOfBounds(std::unique_ptr<Particle> &particle, int selfRow, int selfColumn)
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
    for (auto &particle : particles)
    {
        Dynamics::updatePosition(particle, dt);
        auto outOfBounds = isOutOfBounds(particle, selfRow, selfColumn);

        if (std::get<0>(outOfBounds) != selfRow || std::get<1>(outOfBounds) != selfColumn)
        {
            outOfBoundsParticles.push_back(std::make_tuple(std::move(particle), outOfBounds));
        }
    }
}
std::vector<std::vector<double>> Cell::particlePositions()
{
    std::vector<std::vector<double>> positionMatrix;
    for (auto &particle : particles)
    {
        auto pos = particle->getPosition();
        positionMatrix.push_back(pos);
    }

    return positionMatrix;
};

void Cell::checkCollisions()
{
    for (size_t i = 0; i < particles.size(); ++i)
    {
        for (size_t j = i + 1; j < particles.size(); ++j)
        {
            // Compare particles at index i and j
            auto &particle1 = particles[i];
            auto &particle2 = particles[j];
            if (Dynamics::interactFermionFermion(particle1, particle2))
            {
                Dynamics::collision(particle1, particle2);
            }
        }
    }
}
