#include "node.h"
#include "binheap.h"
#include <stack>
#include <iostream>
#include <vector>


using namespace std;

class graph{
	private:
		int size;   //nodes in graph
		node* nodes;//container for all nodes in graph
		int** matrix;
		binheap* heap;//choose a better name?
		void Explore(node* current, node* destination);//Recursive function that actually looks at nodes and finds shortest path; called by ShortestPath
	public:
		graph():size(0){};
		graph(int graph_size);
		vector<int> ShortestPath(int A, int B);
		void InsertEdge(int from, int to, int weight); //This also updates existing edges
};

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
vector<int> graph::ShortestPath(int start,int end){
	nodes[start].cost = 0;//Setting start cost to 0 because: (1.) logically makes sense (2.) will keep final cost from being off by one (3.) marks the origin conveniently
	node* eyeball = &nodes[start];//Our eye starts at the start point of course
	heap->Insert(eyeball);
	while(!heap->empty() && &(nodes[end]) != heap->Min()){//min method will take a node as a parameter and determine if that node is the root
		
		eyeball = heap->Remove();//go to next item in the heap, and pop it off the heap    
		for(int k=0; k < size; k++){//Iterate through the matrix to find any connections
			
			if(matrix[eyeball->location][k] != -1){//if there's a connection from the eye to the indexed node. Two if statements are for clarity
				if(nodes[eyeball->location].cost + matrix[eyeball->location][k] < nodes[k].cost || nodes[k].cost == -1){//if the eye's distance from orgin + endgelength  less than what the node currently costs
					
						nodes[k].cost = nodes[eyeball->location].cost + matrix[eyeball->location][k];//Change cost of eye node to new total cost
						nodes[k].prev = eyeball;//So eye node will know who changed it
						heap->Insert(&nodes[k]);//Add this to our heap to become our eye at a later point
				}
			}
		}
	}
	
	int current = end;//Now we will trace path from end to beginning
	stack<int> path;//This is where we'll store the final path
	while(current != start){//when current is beginning
		path.push(current);
		current = nodes[current].prev->location;
	}
	
	vector<int> returnPath;
	returnPath.push_back(start);//Don't forget to get start node!
	while(!path.empty()){
		current = path.top();//gets next element off the stack
		path.pop();//removes the retrieved element from the stack
		returnPath.push_back(current);
	}
	
	return returnPath;
}

void graph::InsertEdge(int from, int to, int weight){
	if(from >= 0 && from < size && to >= 0 && to < size){
		matrix[from][to] = weight;
	}
}
