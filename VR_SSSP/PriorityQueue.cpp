#include "PriorityQueue.h"

//=============================================================================
// Class: PriorityQueue
// Function: Default Constructor
// Description: Everything neccessary for the heap is currently handled
//				automatically. I will revisit this after implementing
//				the graph.
// TODO: Revisit after implementing the graph.
//=============================================================================
PriorityQueue::PriorityQueue() {}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: Copy Constructor
// Description: Everything neccessary for the heap is currently handled
//				automatically. I will revisit this after implementing
//				the graph.
// TODO: Revisit after implementing the graph.
//=============================================================================
PriorityQueue::PriorityQueue(const PriorityQueue & src) {}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: Destructor
// Description: Everything neccessary for the heap is currently handled
//				automatically. I will revisit this after implementing
//				the graph.
// TODO: Revisit after implementing the graph.
//=============================================================================
PriorityQueue::~PriorityQueue() {}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: insert
// Description: 
// TODO: None
//=============================================================================
void PriorityQueue::insert(Node * element) {
	minHeap.push_back(element); // Insert node at the end of the vector
	int current = minHeap.size() - 1;
	int parent = (current - 1) / 2;
	
	// upHeap operations
	while (parent >= 0 && minHeap[current]->distance < minHeap[parent]->distance) {
		swap(parent, current);
		current = parent;
		parent = (current - 1) / 2;
	}
}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: pull
// Parameters: None
// Description: 
// TODO: None
//=============================================================================
Node * PriorityQueue::pull() {
	Node * top = minHeap[0]; // Storing for return
	minHeap[0] = minHeap[minHeap.size() - 1]; // Move last item in the heap to the top
	minHeap.pop_back(); //Delete last node in the heap
	unsigned int current = 0;
	
	bool downHeap = (2 * current + 1 < minHeap.size()); // downHeap is true while current has children
	while (downHeap) {
		if (2 * current + 1 >= minHeap.size()) { // Case 1: Current has no children
			downHeap = false;
		}
		else if ((2 * current) + 2 >= minHeap.size()) { // Case 2: If there is no right child
			if (minHeap[current]->distance > minHeap[2 * current + 1]->distance) { //If parent is greater than left child
				swap(current, (2 * current + 1)); 
				current = 2 * current + 1; // Move current down the heap
			}
			downHeap = false;  // Bottom of heap is reached
		}
		else { // Case 3: There is two children
			if (minHeap[current]->distance > minHeap[2 * current + 1]->distance) { // 3a: Left child is the smallest
				swap(current, 2 * current + 1);
				current = 2 * (current + 1);
			}
			else if (minHeap[current]->distance > minHeap[2 * current + 2]->distance) { // 3b: Right child is the smallest
				swap(current, 2 * current + 2);
				current = 2 * current + 2;
			}
			else { // 3c: Both children are greater
				downHeap = false;
			}
		}
	}
	return top;
}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: swap
// Parameters: (int priority_i, int priority_j)
// Description: priority_i becomes priority_j and priority_j becomes priority_i
// TODO: None
//=============================================================================
void PriorityQueue::swap(int priority_i, int priority_j) {
	Node * temp = minHeap[priority_i];
	minHeap[priority_i] = minHeap[priority_j];
	minHeap[priority_j] = temp;
}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: isEmpty
// Parameters: None
// Description: 
// TODO: None
//=============================================================================
bool PriorityQueue::isEmpty() const {
	return minHeap.size() == 0;
}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: peek
// Parameters: None
// Description: 
// TODO: None
//=============================================================================
Node * PriorityQueue::peek() const {
	return minHeap[0];
}
//=============================================================================


//=============================================================================
// Class: PriorityQueue
// Function: printHeap
// Parameters: None
// Description: 
// TODO: None
//=============================================================================
void PriorityQueue::printHeap() const {
	for (unsigned int i = 0; i < minHeap.size(); i++)
		std::cout << minHeap[i]->distance << std::endl;
}
//=============================================================================


