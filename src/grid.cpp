#include "grid.h"
#include "util.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

void Node::UpdateState() {
    CurrentState_ = NextState_;
}

unsigned Node::DetermineNextState() {
    unsigned AmountOfInfectedNeighbours = 0;
    for (auto & y : Neighbours_) {
        AmountOfInfectedNeighbours += y->getCurrentState();
    }
    //double RandomNumber = drawRand();
    double RandomNumber = random_real();
    //std::cout << RandomNumber << std::endl;

    double Product = pow(1 - beta_, AmountOfInfectedNeighbours);
    if (CurrentState_ == 0) {
        if (RandomNumber <= Product) {
            NextState_ = 0;
            return 0;
        }
        else {
            NextState_ = 1;
            return 1;
        }
    }
    else {
        if (RandomNumber <= delta_ * Product) {
            NextState_ = 0;
            return 0;
        }
        else {
            NextState_ = 1;
            return 1;
        }
    }

}

unsigned Node::getCurrentState() const {
    return CurrentState_;
}



void Node::AddNeighbour(Node * y) {
    Neighbours_.push_back(y);
}

Node::Node(double beta, double delta, unsigned index, unsigned infected)
    : beta_(beta), delta_(delta), index_(index), CurrentState_(infected), NextState_(0) {
    if (infected != 0 && infected != 1) {
        throw std::invalid_argument("Infected Nodes can only have value 0 or 1");
    }
}

unsigned Node::getIndex() const {
    return index_;
}

const std::vector<Node *> &Node::getNeighbours() {
    return Neighbours_;
}


unsigned Graph::getAmountOfInfected() const {
    return AmountOfInfected_;
}

void Graph::NextTimeStep() {
    AmountOfInfected_ = 0;
    for (auto& x : NodesInGrid_) {
        AmountOfInfected_ += x.DetermineNextState();
    }
}

void Graph::UpdateGrid() {
    for (auto & x: NodesInGrid_) {
        x.UpdateState();
    }
}

Graph::Graph(unsigned int AmountOfNodes, unsigned AmountOfInfectedNodes, double beta, double delta)
    : AmountOfNodes(AmountOfNodes), NodesInGrid_(), AmountOfEdges_(0) {
    // We beforehand reserve the needed amount of space for NodesInGrid_ such that no reallocation needs
    // to be done. Once we have done that we fill NodesInGrid_ with the requested amount of nodes.
    if (AmountOfInfectedNodes > AmountOfNodes) {
        throw std::invalid_argument("There cannot be more infected nodes than there are nodes");
    }
    NodesInGrid_.reserve(AmountOfNodes);


    for (unsigned i = 0; i < AmountOfInfectedNodes; i++) {
        NodesInGrid_.emplace_back(beta, delta, i, 1);
    }
    for (unsigned i = AmountOfInfectedNodes; i < AmountOfNodes; i++) {
        NodesInGrid_.emplace_back(beta, delta, i, 0);
    }
}

unsigned Graph::addEdge(unsigned int i, unsigned int j) {
    if (i >= AmountOfNodes || j >= AmountOfNodes) {
        throw std::invalid_argument("Nodes are outside of the range");
    }
    if (i == j) {
        return 0;
    }
    for (auto x : NodesInGrid_[i].getNeighbours()) {
        if (x->getIndex() == j) {
            return 0;
        }
    }
    NodesInGrid_[i].AddNeighbour(&NodesInGrid_[j]);
    NodesInGrid_[j].AddNeighbour(&NodesInGrid_[i]);
    AmountOfEdges_++;
    return 1;
}

void Graph::OneStep() {
    NextTimeStep();
    UpdateGrid();
}

unsigned Graph::getAmountOfEdges() const {
    return AmountOfEdges_;
}

std::vector<double> Graph::MatrixMult(std::vector<double> &x) {
    if (x.size() != AmountOfNodes) {
        throw std::invalid_argument("Dimensions of vector and adjencency matrix are not equal");
    }
    std::vector<double> y (x.size(), 0);
    for (unsigned i = 0; i < x.size(); i++) {
        for (auto j : NodesInGrid_[i].getNeighbours()) {
            y[i] += x[j->getIndex()];
        }
    }
    return y;
}

std::vector<unsigned> RunModel(Graph &G, unsigned int EndTime) {
    std::vector<unsigned> Output;
    for (unsigned i = 0; i < EndTime; i++) {
        G.OneStep();
        Output.push_back(G.getAmountOfInfected());
        if (G.getAmountOfInfected() == 0) {
        }
    }
    return Output;
}

/*
void MakeNodesInfected(Graph &G, unsigned int n) {
    for (unsigned i = 0; i < n; i++) {
        G.NodesInGrid_[i].MakeInfected();
    }
} */
