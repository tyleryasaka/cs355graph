#ifndef NODE_H
#define NODE_H


//=============================================================================
// Class: Node
// Description: Node object to be used with a shortest-path graph.
// TODO: Build accessor functions for data members
//=============================================================================
class Node{
public:
	// Constructors - Overloading
	Node();
	~Node();

	// Friends
	friend class PriorityQueue;
	friend class Graph;

	// Mutators
	
	// Accessors
private:
	int distance;
	int location;
	Node * previous;
	bool visited;
};
//=============================================================================


#endif
