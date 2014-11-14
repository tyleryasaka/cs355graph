#include <vector>
using namespace std;

class binheap;

struct node {
	friend class binheap;
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in path
};

#include "binheap.h"

class graph{
	private:
		vector<node>* edges;//Our adjacency list
		binheap heap;//choose a better name?
		void Explore(node* from, node* to);//Recursive function that actually looks at nodes and finds shortest path; called by ShortestPath
	public:
		node** ShortestPath(node* A, node* B);//returns array of pointers (pointer to pointers)
};
