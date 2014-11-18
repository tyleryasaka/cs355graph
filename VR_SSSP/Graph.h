#ifndef GRAPH_H
#define GRAPH_H

#include "PriorityQueue.h"
#include "Node.h"
#include <vector>

//=============================================================================
// Class: Graph
// Description: 
// TODO: 
//=============================================================================
class Graph {
public:
	// Constructors - Overloading
	Graph();
	Graph(int vertexCount);
	Graph(const Graph & src);
	~Graph();

	// Mutators
	void insertEdge(int i, int j, int weight);
	void removeEdge(int i, int j, int weight);

	// Accessors
	void sssp(int source);
	
private:
	int vertexCount;
	std::vector<Node *> explored;
	std::vector<Node *> shortestPath;
	int ** adjacencyMatrix;
	Node * vertices;
	PriorityQueue pQueue;
};
//=============================================================================


#endif
