#include <iostream>
#include "binheap.h"
#include "graph.h"
int main(){
	graph path(6);
	
	path.InsertEdge(0,1,5);
	path.InsertEdge(1,2,6);
	path.InsertEdge(2,4,6);
	path.InsertEdge(1,3,3);
	path.InsertEdge(3,5,2);
	path.InsertEdge(5,4,6);
	
	path.ShortestPath(0,4);
	
	
	return 0;
}

