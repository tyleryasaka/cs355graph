#include <vector>
using namespace std;

class binheap;

struct node {
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in path
};

#include "binheap.h"

class graph{
	private:
		//Our adjacency list
		//The first item can be the index node, while the others can be all the nodes
		//adjacent to the index node
		vector<node>* edges;
		edgecount;//keeps track of how many edges we have
		binheap heap;//choose a better name?
		node ** path;//variable that will store the path found
		void Explore(node* current, node* destination);//Recursive function that actually looks at nodes and finds shortest path; called by ShortestPath
	public:
		node** ShortestPath(node* A, node* B);//returns array of pointers (pointer to pointers)
};

graph::ShortestPath(node* A,node* B){
	Explore(A,B);
	return path;//path will be set by Explore
}

graph::Explore(node* current, node* origin, node* destination){
	//loop through vector to find current node; (more efficient way than this?)
	for(i = 0; i < edgecount; i++){
		//Check if this is the node we are looking for
		if(edges[i].front()==current) {
			//Loop through vector to explore all edges of this node
			//i starts at beginning +1 because we are using first item as the node to relate the other items to
			//So essentially the 2nd item in the list is the first item that is adjacent to 
			for(i = edges.begin()+1; i < edges.end(); i++){
				//Here call Explore recursively on all items that have a shorter cost
			}
		}
		//Somewhere down here, we'll have to check to see if we know
		//mathematically that this has to be the minimum path,
		//or if this is the last path in the heap.
		//
		//If it is the minimum or the last path, we'll take the minimum
		//off the heap and use a while loop to follow the path backwards,
		//in the meantime storing each node along this minimum
		//path into our "path" variable as a pointer.
		//Once it reaches the origin it will fall out of the while loop
		//and the pointers in the "path" array will be reversed
		//(since we added them in backwards order).
		//
	}
}
