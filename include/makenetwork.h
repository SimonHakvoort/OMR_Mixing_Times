#pragma once

#include "network.h"

// Places N edges randomly in the grid
void PlaceNEdges(Network & G, unsigned N);

// Places each edge with a specified probability p
unsigned EdgeWithProb(Network & G, double p);

// Places edges for node i to nodes i - 1 and i + 1
void CircularGraph(Network & G);
