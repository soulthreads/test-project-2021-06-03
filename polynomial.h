#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <ostream>

using CoefficientType = float;

class Polynomial
{
public:
    // The terms are defined from highest degree to lowest in constructor
    Polynomial(std::initializer_list<CoefficientType> coeffs);

    const std::vector<CoefficientType>& coefficients() const;

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
    bool operator==(const Polynomial& other) const;

private:
    std::vector<CoefficientType> _coeffs;
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p);

#endif // POLYNOMIAL_H
