// VectorMath.cpp

#include "VectorMath.h"

namespace VectorMath
{
    double norm(const std::vector<double> &vector)
    {
        double sum = 0.0;
        for (double v_i : vector)
        {
            sum += v_i * v_i;
        }
        return std::sqrt(sum);
    }
    double dotProduct(const std::vector<double> &vector1, const std::vector<double> &vector2)
    {
        if (vector1.size() != vector2.size())
        {
            throw std::runtime_error("Error at dot product: vectors must have the same size!");
        }
        double product = 0.0;

        for (size_t i = 0; i < vector1.size(); i++)
        {
            product += vector1[i] * vector2[i];
        }
        return product;
    }

    std::vector<double> subtraction(const std::vector<double> &vector1, const std::vector<double> &vector2)
    {
        if (vector1.size() != vector2.size())
        {
            throw std::runtime_error("Error at subtraction: vectors must have the same size!");
        }
        std::vector<double> subtracted;

        for (size_t i = 0; i < vector1.size(); i++)
        {
            subtracted.push_back(vector1[i] - vector2[i]);
        }
        return subtracted;
    }

}
