#include "grid.h"
#include "makegraph.h"
#include <iostream>
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    unsigned iterations = 2000;
    unsigned NumberOfNodes = 2000;
    unsigned NumberOfInfectedNodes = 500;
    double beta = 0.0125;
    double delta = 0.2;

    Graph G {NumberOfNodes, NumberOfInfectedNodes, beta, delta};
    PlaceNEdges(G, 16000);


    std::vector<unsigned> x = RunModel(G, iterations);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / pow(10,6)<< "[µs]" << std::endl;

    for (unsigned i = 0; i < iterations; i++) {
        std::cout << x[i] << std::endl;
    }
    std::cout << (1 - delta) + beta * G.SpectralRadius(0.000001) << std::endl;
};