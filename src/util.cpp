
#include "util.h"

double random_real(double a, double b) {
    auto distribution = std::uniform_real_distribution<double>(a, b);
    return distribution(engine);
}

unsigned random_int(unsigned int nmax) {
    auto distribution = std::uniform_int_distribution<unsigned>(0, nmax - 1);
    return distribution(engine);
}
