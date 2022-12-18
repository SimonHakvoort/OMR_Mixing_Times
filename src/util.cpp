
#include "util.h"
#include <cmath>

double random_real(double a, double b) {
    auto distribution = std::uniform_real_distribution<double>(a, b);
    return distribution(engine);
}

unsigned random_int(unsigned int nmax) {
    auto distribution = std::uniform_int_distribution<unsigned>(0, nmax - 1);
    return distribution(engine);
}

double NormVector(const std::vector<double> & x) {
    double total = 0;
    for (double i : x) {
        total += pow(i, 2);
    }
    return sqrt(total);
}
