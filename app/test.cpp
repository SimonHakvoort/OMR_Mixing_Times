#include "grid.h"
#include "makegraph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    unsigned iterations = 10000;

    unsigned NumberOfNodes = 100000;
    unsigned NumberOfInfectedNodes = 50000;
    unsigned NumberOfEdges = 1000000;

    double beta = 0.04;
    double delta = 0.8;
    Graph G {NumberOfNodes, NumberOfInfectedNodes, beta, delta};
    //CircularGraph(G);



    PlaceNEdges(G, NumberOfEdges);


    std::vector<unsigned> x = RunModel(G, iterations);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / pow(10,6)<< " seconds" << std::endl;

    std::ofstream OutputFile;
    OutputFile.open("verwijderen.txt");
    if (OutputFile.is_open()) {
        for (unsigned i = 0; i < iterations - 1; i++) {
            OutputFile << x[i] << ", " << "\n";
        }
    }
    OutputFile.close();
    std::cout << beta * G.SpectralRadius(0.0000001) / delta << std::endl;

    return 0;
};