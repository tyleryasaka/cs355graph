#include <iostream>
#include "binheap.h"
#include "graph.h"
#include "path.h"
using namespace std;

void PrintPath(path route);

int main(){
	graph map(10);
	
	map.InsertEdge(0,3,2);
	map.InsertEdge(0,8,13);
	map.InsertEdge(1,0,15);
	map.InsertEdge(1,4,6);
	map.InsertEdge(2,1,1);
	map.InsertEdge(3,1,40);
	map.InsertEdge(3,6,8);
	map.InsertEdge(4,3,3);
	map.InsertEdge(5,2,1);
	map.InsertEdge(5,9,6);
	map.InsertEdge(6,8,2);
	map.InsertEdge(7,3,3);
	map.InsertEdge(7,5,3);
	map.InsertEdge(8,7,7);
	map.InsertEdge(8,9,6);
	map.InsertEdge(9,7,2);
	
	path route = map.ShortestPath(4,9);
	PrintPath(route);
	
	return 0;
}

void PrintPath(path route){
	cout << endl << "Path:" << endl;
	
	for(int i=0;i<route.length;i++){
		cout << route.location[i] << endl;
	}
	
	cout << endl;
}
