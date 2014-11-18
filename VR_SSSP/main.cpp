#include "Graph.h"

int main() {
	
	Graph G(4);
	
	G.insertEdge(0, 1, 1);
	G.insertEdge(0, 2, 1);
	G.insertEdge(1, 3, 1);
	G.insertEdge(2, 3, 2);
	
	G.sssp(0);
		
	return 0;
}
