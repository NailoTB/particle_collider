// VectorMath.h

#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <cmath>
#include <memory>
#include <vector>
#include <iostream>

namespace VectorMath
{
    double norm(const std::vector<double> &);
    double dotProduct(const std::vector<double> &, const std::vector<double> &);
    std::vector<double> subtraction(const std::vector<double> &, const std::vector<double> &);

}

#endif // VECTORMATH_H
