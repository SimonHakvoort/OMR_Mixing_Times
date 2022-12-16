#include "makegraph.h"
#include "grid.h"
#include "util.h"
#include <stdexcept>
#include <iostream>


void PlaceNEdges(Graph &G, unsigned int N) {
    unsigned EdgesPlaced = 0;
    if (G.getAmountOfEdges() + N >= G.AmountOfNodes * (G.AmountOfNodes - 1)) {
        throw std::invalid_argument("Cannot place that many edges in this graph");
    }
    while (EdgesPlaced < N) {
        unsigned FirstNode = random_int(G.AmountOfNodes);
        unsigned SecondNode = random_int(G.AmountOfNodes);
        EdgesPlaced += G.addEdge(FirstNode, SecondNode);
    }
}

unsigned EdgeWithProb(Graph &G, double p) {
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
