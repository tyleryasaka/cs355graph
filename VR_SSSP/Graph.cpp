#include "Graph.h"
#include <climits>
#include <iostream>


//=================================================================================================
// Class: Graph
// Function: Default Constructor
// Parameters: None
// Description: 
// TODO:
//=================================================================================================
Graph::Graph(){}
//=================================================================================================


//=================================================================================================
// Class: Graph
// Function: Overloaded Constructor
// Parameters: (int vertexCount)
// Description: Initializes adjacencyMatrix as a symmetric matrix of size
//				vertexCount^2. 
//				All distances are initialized to infinity and previous 
//				vertices are set to null.
// TODO:
//=================================================================================================
Graph::Graph(int vertexCount) {
	this->vertexCount = vertexCount;
	vertices = new Node[vertexCount];
	adjacencyMatrix = new int*[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		vertices[i].location = i;
		vertices[i].distance = INT_MAX;
		adjacencyMatrix[i] = new int[vertexCount];
		for (int j = 0; j < vertexCount; j++)
			adjacencyMatrix[i][j] = -1;
	}	
}
//=================================================================================================


//=================================================================================================
// Class: Graph
// Function: Copy Constructor
// Parameters: (const Graph & src)
// Description: 
// TODO:
//=================================================================================================
Graph::Graph(const Graph & src) {}
//=================================================================================================


//=================================================================================================
// Class: Graph
// Function: Destructor
// Parameters: None
// Description: Deallocates the memory allocated by the adjacencyMatrix.
// TODO: Test this
//=================================================================================================
Graph::~Graph() {
	for (int i = 0; i < vertexCount; i++)
		delete [] adjacencyMatrix[i];
	delete [] adjacencyMatrix;
	delete [] vertices;
}
//=================================================================================================


//=================================================================================================
// Class: Graph
// Function: sssp "Single-Source Shortest Path"
// Parameters: (int i , int j)
// Description: Adds a directed edge to the graph. 
// TODO: Accessor functions need to be added for vertex data members. Will need to change here.
//=================================================================================================
void Graph::sssp(int source) {
	Node * probe;
	int probeSensor;
	for (int i = 0; i < vertexCount; i++) {
		if (i == source) {
			vertices[source].distance = 0;
			pQueue.insert(&vertices[source]);
		}
		else 
			vertices[i].distance = INT_MAX;
	}
	while (!pQueue.isEmpty()) {
		probe = pQueue.pull();
		explored.push_back(probe);
		for (int i = 0; i < vertexCount; i++) {
			probeSensor = adjacencyMatrix[probe->location][i];
			if ((probeSensor != -1) && (probe->distance + probeSensor) < vertices[i].distance) {
				vertices[i].distance = probe->distance + probeSensor;
				vertices[i].previous = probe;
				pQueue.insert(&vertices[i]);
			}
		}
	}
}
//=================================================================================================


//=================================================================================================
// Class: Graph
// Function: insertEdge
// Parameters: (int i , int j)
// Description: Adds a directed edge to the graph. 
// TODO: 
//=================================================================================================
void Graph::insertEdge(int i, int j, int weight) {
	if ((i >= 0 && i < vertexCount) && (j >= 0 && j < vertexCount)) {
		adjacencyMatrix[i][j] = weight;
	}
}
//=================================================================================================


//=================================================================================================
// Class: Graph
// Function: removeEdge
// Parameters: (int i , int j)
// Description: Removes an undirected edge from the graph. 
// TODO: 
//=================================================================================================
void Graph::removeEdge(int i, int j, int weight) {
	if ((i >= 0 && i < vertexCount) && (j >= 0 && j < vertexCount)) {
		adjacencyMatrix[i][j] = weight;
	}
}
//=================================================================================================


