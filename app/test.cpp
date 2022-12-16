#include "grid.h"
#include "makegraph.h"
#include <iostream>
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    unsigned iterations = 1000;
    unsigned NumberOfNodes = 200;
    unsigned NumberOfInfectedNodes = 10;
    double beta = 0.11;
    double delta = 0.99;

    Graph G {NumberOfNodes, NumberOfInfectedNodes, beta, delta};
    PlaceNEdges(G, 1000);


    std::vector<unsigned> x = RunModel(G, iterations);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / pow(10,6)<< "[µs]" << std::endl;
    for (unsigned i = 0; i < iterations; i++) {
        std::cout << x[i] << std::endl;
    }
};