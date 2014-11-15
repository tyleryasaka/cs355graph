#include <iostream>
#include "binheap.h"
#include "graph.h"

void PrintPath(vector<int> path);

int main(){
	graph map(7);
	
	map.InsertEdge(0,3,1);
	map.InsertEdge(0,5,3);
	map.InsertEdge(1,0,10);
	map.InsertEdge(1,6,1);
	map.InsertEdge(2,1,3);
	map.InsertEdge(2,4,1);
	map.InsertEdge(3,5,1);
	map.InsertEdge(4,1,1);
	map.InsertEdge(4,0,20);
	map.InsertEdge(4,3,20);
	map.InsertEdge(6,0,1);
	map.InsertEdge(6,5,5);
	
	vector<int> path = map.ShortestPath(2,5);
	PrintPath(path);
	
	return 0;
}

void PrintPath(vector<int> path){
	cout << endl << "Path:" << endl;
	
	for(vector<int>::iterator i = path.begin() ; i != path.end(); i++){
		cout << *i << endl;
	}
	
	cout << endl;
}
