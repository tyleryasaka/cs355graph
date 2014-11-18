
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <iostream>
#include "Node.h"


//=============================================================================
// Class: PriorityQueue
// Description: PriorityQueue implemented using a binary min heap.
// 			    The heap is implemented using a vector of node *'s.
// TODO: Revisit after graph implementation
//=============================================================================
class PriorityQueue {
public:
	// Constructors - Overloading
	PriorityQueue();
	PriorityQueue(const PriorityQueue & src);
	PriorityQueue & operator=(const PriorityQueue & src);
	~PriorityQueue();
	
	// Mutators
	void insert(Node * element);
	Node * pull();
	
	// Accessors
	bool isEmpty() const;
	Node * peek() const;
	void printHeap() const;
		
private:
	void swap(int priority_i, int priority_j);
	
	std::vector<Node *> minHeap;
};
//=============================================================================


#endif


