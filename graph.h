#include "node.h"
class binheap;
#include "binheap.h"
#include <stack>
#include <iostream>
using namespace std;

class graph{
	private:
		int size;   //nodes in graph
		node* nodes;//container for all nodes in graph
		int** matrix;
		binheap* heap;//choose a better name?
		node ** path;//array that will store the path found; better ideas for this?
		void Explore(node* current, node* destination);//Recursive function that actually looks at nodes and finds shortest path; called by ShortestPath
	public:
		graph():size(0){};
		graph(int graph_size);
		stack<int> ShortestPath(int A, int B);
		void InsertEdge(int from, int to, int weight); //This also updates existing edges
};
/*
node node::operator=(const node &n){
	cost = n.cost;
	prev = n.prev;
	location = n.location;
	return *this;
}
*/

//overloaded constructor
graph::graph(int graph_size){
	size = graph_size;
	nodes = new node[size];
	matrix = new int*[size];
	heap = new binheap(size);

	for(int i=0;i<size;i++){
		nodes[i].cost = -1;           
		nodes[i].prev = 0;
		nodes[i].location = i;
		matrix[i] = new int[size];
		for(int j=0;j<size;j++){
			matrix[i][j] = -1;
		}
	}
}

//input: indeces of nodes in matrix for begin and end point of desired path
//output: for now, array of indeces could be set to object's "path" array for shortest path... maybe change to LinkedList?
stack<int> graph::ShortestPath(int A,int B){
	int eye = A;  
	node startNode = nodes[eye];
	node eyeNode = nodes[eye];
	int end = B;
	
	heap->Insert(&eyeNode);
	stack<int> path;

	while(!heap->empty() && &(nodes[end]) != heap->Min()){             //root method will take a node as a parameter and determine if that node is the root
														//if end holds the smallest value in heap you know you reached the shortest path because 											//all other nodes are further from the orgin
		for(int k=0; k < size; k++){
			if(matrix[eye][k] != -1){      //if there's a connection from the eye to the indexed node. Two if statements are for clarity
				if(nodes[eye].cost + matrix[eye][k] < nodes[k].cost || nodes[k].cost == -1){   //if the eye's distance from orgin + endgelength  less than what the node currently costs
						nodes[k].cost = nodes[eye].cost + matrix[eye][k];
						nodes[k].prev = &eyeNode;
						cout<<eye<<" is connected to "<<nodes[k].location<<endl;
						heap->Insert(&nodes[k]);
				}
				//if the path is longer nothing changes
			}
		}
		cout<<eye<<endl;  //this should change to 1 instead it stays at 0
		eyeNode = *(heap->Remove());              
		eye = eyeNode.location;
	}
	
	
	if(eye != end){
		cout<<"Path is not connected";
	}
	
	else{
		while(eyeNode.location != startNode.location){
			path.push(eyeNode.location);
			eyeNode = *(eyeNode.prev);
		}
		path.push(startNode.location);
	}
	


	
	cout<<endl;
	
	
	return path;

		
}










void graph::InsertEdge(int from, int to, int weight){
	if(from >= 0 && from < size && to >= 0 && to < size){
		matrix[from][to] = weight;
	}
}
