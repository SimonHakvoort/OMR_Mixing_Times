#include "grid.h"
#include "makegraph.h"
#include <iostream>
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    unsigned iterations = 1000;
    unsigned NumberOfNodes = 6;
    unsigned NumberOfInfectedNodes = 1;
    double beta = 0.05;
    double delta = 0.4;

    Graph G {NumberOfNodes, NumberOfInfectedNodes, beta, delta};
    PlaceNEdges(G, 10);


    std::vector<unsigned> x = RunModel(G, iterations);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / pow(10,6)<< "[µs]" << std::endl;
    /*
    for (unsigned i = 0; i < iterations; i++) {
        std::cout << x[i] << std::endl;
    } */
    std::vector<double> vec {1,2,3,4,5,6};
    std::vector y = G.MatrixMult(vec);
    for (unsigned i = 0; i < 6; i++) {
        std::cout << y[i] << std::endl;
    }
};