#include "grid.h"
#include "makegraph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    unsigned PowerOfTwo = 13;

    unsigned AmountOfGraphs = 200;
    unsigned iterations = 10000;

    unsigned NumberOfNodes = pow(2, PowerOfTwo);
    unsigned NumberOfInfectedNodes = pow(2, PowerOfTwo - 1);
    unsigned NumberOfEdges = pow(2, PowerOfTwo + 3);

    double beta = 0.04;
    double delta = 0.8;
    std::vector<Graph> VectorOfGraphs;
    std::vector<unsigned> VectorOfTimes;
    for (unsigned i = 0; i < AmountOfGraphs; i++) {
        VectorOfGraphs.emplace_back(NumberOfNodes, NumberOfInfectedNodes, beta, delta);
        PlaceNEdges(VectorOfGraphs[i], NumberOfEdges);
    }

    for (unsigned i = 0; i < AmountOfGraphs; i++) {
        VectorOfTimes.push_back(TimeUntilZero(VectorOfGraphs[i], iterations));
        std::cout << VectorOfTimes[i] << "," << std::endl;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::ofstream OutputFile;
    OutputFile.open("tijden16.txt");
    if (OutputFile.is_open()) {
        for (unsigned i = 0; i < iterations; i++) {
            OutputFile << VectorOfTimes[i] << ", " << "\n";
        }
    }
    OutputFile.close();
    std::cout << beta * VectorOfGraphs[0].SpectralRadius(0.0000001) / delta<< std::endl;
    return 0;
    //std::cout << (1 - delta) + beta * VectorOfGraphs[0].SpectralRadius(0.0000001) << std::endl;
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / pow(10,6)<< " seconds" << std::endl;
};