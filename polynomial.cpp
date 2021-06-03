#include "polynomial.h"
#include <algorithm>

Polynomial::Polynomial(std::initializer_list<CoefficientType> coeffs)
    : _coeffs(rbegin(coeffs), rend(coeffs))
{
    if (coeffs.size() == 0) {
        _coeffs.push_back(0);
    }
}

const std::vector<CoefficientType> &Polynomial::coefficients() const
{
    return _coeffs;
}

Polynomial Polynomial::operator+(const Polynomial &right) const
{
    Polynomial result{};

    const size_t left_degree = _coeffs.size();
    const size_t right_degree = right._coeffs.size();
    const size_t min_degree = std::min(left_degree, right_degree);
    const size_t max_degree = std::max(left_degree, right_degree);
    const Polynomial& max_p = (left_degree > right_degree) ? *this : right;

    result._coeffs.resize(max_degree, 0);

    // First add appropriate terms of each polynomial together
    for (size_t i = 0; i < min_degree; ++i) {
        result._coeffs[i] = _coeffs[i] + right._coeffs[i];
    }
    // Then add the rest of the terms from the max degree polynomial
    for (size_t i = min_degree; i < max_degree; ++i) {
        result._coeffs[i] = max_p._coeffs[i];
    }

    // Check if highest coefficients cancelled each other out
    for (size_t i = max_degree - 1; i > 0; --i) {
        if (result._coeffs[i] == 0) {
            result._coeffs.resize(i); // drop the highest coefficient
        } else {
            break;
        }
    }

    return result;
}

Polynomial Polynomial::operator*(const Polynomial &right) const
{
    Polynomial result{};

    const size_t left_degree = _coeffs.size();
    const size_t right_degree = right._coeffs.size();
    // If one of the polynomials is just "0", return 0
    if ((left_degree == 1 && _coeffs[0] == 0) ||
        (right_degree == 1 && right._coeffs[0] == 0))
    {
        return result;
    }

    const size_t result_degree = left_degree + right_degree - 1;

    result._coeffs.resize(result_degree, 0);

    // Add products of each combination of the terms
    for (size_t i = 0; i < left_degree; ++i) {
        for (size_t j = 0; j < right_degree; ++j) {
            result._coeffs[i+j] += _coeffs[i] * right._coeffs[j];
        }
    }

    return result;
}

bool Polynomial::operator==(const Polynomial &other) const
{
    return _coeffs == other._coeffs;
}

std::ostream& operator<<(std::ostream &os, const Polynomial& p)
{
    for (size_t i = p.coefficients().size() - 1; i > 0; --i) {
        os << p.coefficients()[i] << " x^" << i << " + ";
    }

    os << p.coefficients()[0];

    return os;
}
