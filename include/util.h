#pragma once

#include <random>

static std::random_device rd;
static std::default_random_engine engine(rd());

// Produces a random number between 0 and 1
double random_real(double a = 0.0, double b = 1.0);

// Produces a random integer between 0 and nmax-1
unsigned random_int(unsigned nmax);