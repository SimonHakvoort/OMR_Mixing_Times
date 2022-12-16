#pragma once

#include "grid.h"

// Places N edges randomly in the grid
void PlaceNEdges(Graph & G, unsigned N);

// Places each edge with a specified probability p
unsigned EdgeWithProb(Graph & G, double p);
