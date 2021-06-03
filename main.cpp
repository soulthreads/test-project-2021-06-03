#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "polynomial.h"

TEST_CASE("Testing the Polynomial class") {
    const Polynomial p0{};
    // In our case empty polynomial has zeroth degree with coeff. 0
    CHECK(p0.coefficients().size() == 1);
    CHECK(p0.coefficients()[0] == 0);

    const Polynomial p1{1, 1};
    const Polynomial p2{1, -1};
    const Polynomial p3{1, 2, 1};
    const Polynomial p4{-1, 1};

    SUBCASE("Addition") {
        SUBCASE("Add zero") {
            const auto p = p0 + p1;
            CHECK(p == Polynomial{1, 1});
        }

        SUBCASE("Add two equal degree polynomials") {
            const auto p = p1 + p2;
            CHECK(p == Polynomial{2, 0});
        }

        SUBCASE("Add two different degree polynomials") {
            const auto p = p1 + p3;
            CHECK(p == Polynomial{1, 3, 2});
        }

        SUBCASE("Add polynomials with terms cancelling out") {
            const auto p = p1 + p4;
            CHECK(p == Polynomial{2});
        }
    }

    SUBCASE("Multiplication") {
        SUBCASE("Multiply by zero") {
            const auto p = p0 * p1;
            CHECK(p == Polynomial{0});
        }

        SUBCASE("Normal multiplication") {
            CHECK((p1 * p2) == Polynomial{1, 0, -1});
            CHECK((p1 * p3) == Polynomial{1, 3, 3, 1});
        }
    }
}
