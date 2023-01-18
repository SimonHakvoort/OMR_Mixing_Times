#include "makenetwork.h"
#include "network.h"
#include "util.h"
#include <stdexcept>
#include <iostream>


void PlaceNEdges(Network &G, unsigned int N) {
    unsigned EdgesPlaced = 0;
    if (G.getAmountOfEdges() + N >= G.AmountOfNodes * (G.AmountOfNodes - 1) / 2) {
        throw std::invalid_argument("Cannot place that many edges in this graph");
    }
    while (EdgesPlaced < N) {
        unsigned FirstNode = random_int(G.AmountOfNodes);
        unsigned SecondNode = random_int(G.AmountOfNodes);
        EdgesPlaced += G.addEdge(FirstNode, SecondNode);
    }
}

unsigned EdgeWithProb(Network &G, double p) {
    unsigned EdgesPlaced = 0;
    for (unsigned i = 0; i < G.AmountOfNodes; i++) {
        for (unsigned j = i+1; j < G.AmountOfNodes; j++) {
            if (random_real() <= p) {
                EdgesPlaced += G.addEdge(i, j);
            }
        }
    }
    return EdgesPlaced;
}

void CircularGraph(Network &G) {
    for (unsigned i = 0; i < G.AmountOfNodes - 1; i++) {
        G.addEdge(i, i+1);
    }
    G.addEdge(0, G.AmountOfNodes - 1);
}
