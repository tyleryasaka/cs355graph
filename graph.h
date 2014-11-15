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
stack<int> graph::ShortestPath(int start,int end){
	start->cost = 0;//Setting start cost to 0 because: (1.) logically makes sense (2.) will keep final cost from being off by one (3.) marks the origin conveniently
	int eyeball = start;//Our eye starts at the start point of course
	heap->Insert(eyeNode);
	stack<int> path;//This is where we'll store the final path
	while(!heap->empty() && &(nodes[end]) != heap->Min()){//min method will take a node as a parameter and determine if that node is the root
		
		nodes[eyeball] = heap->Remove();//go to next item in the heap, and pop it off the heap    
		eye = nodes[eyeball]->location;//this is the matrix location of our new node
		for(int k=0; k < size; k++){//Iterate through the matrix to find any connections
			
			if(matrix[eye][k] != -1){//if there's a connection from the eye to the indexed node. Two if statements are for clarity
				if(nodes[eyeball].cost + matrix[eyeball][k] < nodes[k].cost || nodes[k].cost == -1){//if the eye's distance from orgin + endgelength  less than what the node currently costs
					
						nodes[k].cost = nodes[eyeball].cost + matrix[eyeball][k];//Change cost of eye node to new total cost
						nodes[k].prev = nodes[eyeball];//So eye node will know who changed it
						heap->Insert(&nodes[k]);//Add this to our heap to become our eye at a later point
				}
			}
		}
	}
	
	int current = end;//Now we will trace path from end to beginning
	while(current != start){//when current is beginning
		path.push(current);
		current = nodes[current].prev->location;
	}
	
	return path;//Replace this.

		
}










void graph::InsertEdge(int from, int to, int weight){
	if(from >= 0 && from < size && to >= 0 && to < size){
		matrix[from][to] = weight;
	}
}
