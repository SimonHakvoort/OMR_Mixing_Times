#pragma once

#include <vector>
#include <array>
#include <random>

// With matrix vector mult keep in mind that the matrix is symmetric and

class Node {
protected:
    // index_ is a unique index given to each node.
    const unsigned index_;

    // CurrentState_ indicates whether a Node is infected (1) or not (0) at the current iteration
    unsigned CurrentState_;

    // NextState_ indicates whether a Node will be infected (1) or not (0) at the next iteration
    unsigned NextState_;

    // Constants beta_ and delta_ are stored in each Node
    const double beta_;
    const double delta_;

    // The vector Neighbours_ contains pointers to Nodes (memory adresses where Nodes are stored) of neighbouring nodes
    std::vector<Node*> Neighbours_;
public:
    // The getNeighbours function is a getter that returns a const reference of Neighbours_ (to make sure  that
    // it cannot be changed)
    const  std::vector<Node*> & getNeighbours();

    // Returns the index
    [[nodiscard]] unsigned getIndex() const;

    // A Node constructor
    Node(double beta, double delta, unsigned index, unsigned infected);

    // Adds a pointer of a Node to Neighbours_
    void AddNeighbour(Node * y);

    // Function that determines the next state based on the probabilities from the article
    unsigned DetermineNextState();

    // Changes CurrentState_ to NextState_
    void UpdateState();

    // Returns the CurrentState_
    unsigned getCurrentState() const;

    // Makes the Node infected (only used during the initialization of the grid)
    //void MakeInfected();
};

class Graph {
protected:
    // To keep track of the amount of infected nodes
    unsigned AmountOfInfected_;

    // A vector containing all the Nodes from the grid
    std::vector<Node> NodesInGrid_;

    unsigned AmountOfEdges_;
public:
    // Constructor of a graph, that immediatly generates a specified amount of Nodes
    // It will make Nodes 0 <= i < AmountOfInfectedNodes infected in the initial state, something to keep
    // in mind when placing the edges
    Graph(unsigned AmountOfNodes, unsigned AmountOfInfectedNodes, double beta, double delta);

    // Getter for the amount of infected and amount of edges
    unsigned getAmountOfInfected() const;
    unsigned getAmountOfEdges() const;


    // Computes DetermineNextState for all the Nodes in the grid
    void NextTimeStep();

    // Performs UpdateState for all the Nodes in the Grid
    void UpdateGrid();

    // Performs NextTimeStep() and UpdateGrid()
    void OneStep();

    const unsigned AmountOfNodes;

    // Returns 1 if edge is placed, 0 if edge already exists
    unsigned addEdge(unsigned i, unsigned j);

    // Multiply a vector with the adjecency matrix of the grid
    std::vector<double> MatrixMult(std::vector<double> & x);

    double SpectralRadius(double epsilon);
};

std::vector<unsigned> RunModel(Graph & G, unsigned EndTime);

unsigned TimeUntilZero(Graph & G, unsigned MaxIter);

//void MakeNodesInfected(Graph & G, unsigned n);



