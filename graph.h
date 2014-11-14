#include <vector>
using namespace std;

class binheap;

struct node {
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in tentative path
    int location;//index of this node on matrix
    node operator=(const node &n);
};

#include "binheap.h"

class graph{
	private:
		int size;//number of nodes in graph
		node* nodes;//container for all nodes in graph; indeces correspond to 1st matrix indeces
		//matrix:
		//this will be a 2d array that stores weighted edge values, or -1 for nonexistent
		int** matrix;
		binheap* heap;//choose a better name?
		node ** path;//array that will store the path found; better ideas for this?
		void Explore(node* current, node* destination);//Recursive function that actually looks at nodes and finds shortest path; called by ShortestPath
	public:
		graph():size(0){};
		graph(int graph_size);
		void ShortestPath(int A, int B);//returns array of indeces of shortest path.. I'm thinking we should use LinkedList here instead
		//I added insert edge just for convenience.
		//Technically it's not necessary since our graph can be static,
		//but it seems much simpler to add edges by making a simple
		//function call in our driver program, rather than
		//doing it with overloaded constructor parameters
		//or some other weird jazz.
		//By the way we, shouldn't need a function to remove edges.
		void InsertEdge(int from, int to, int weight);//This also updates existing edges
};

node node::operator=(const node &n){
	cost = n.cost;
	prev = n.prev;
	location = n.location;
	return *this;
}

//overloaded constructor
graph::graph(int graph_size){
	size = graph_size;
	nodes = new node[size];
	matrix = new int*[size];
	heap = new binheap(size);
	//create nodes, insert them into matrix, and map them to matrix
	for(int i=0;i<size;i++){
		//create node, and store in matrix[i][i]
		//(this is more efficient than creating a separate array.
		//since we won't allow an edge between a node and itself,
		//it is ok to use matrix[i][i] for this purpose.)
		nodes[i].cost = -1;//using -1 to represent infinity
		nodes[i].prev = 0;//referrer is null by default
		nodes[i].location = i;//this way a node knows its location in the matrix and list
		//set all edges to empty (represented by -1)
		matrix[i] = new int[size];
		for(int j=0;j<size;j++){
			matrix[i][j] = -1;
		}
	}
}

//input: indeces of nodes in matrix for begin and end point of desired path
//output: for now, array of indeces could be set to object's "path" array for shortest path... maybe change to LinkedList?
void graph::ShortestPath(int A,int B){
	node* a = &nodes[A];//get actual node pointer corresponding index from list
	node* b = &nodes[B];
	a->cost = 0;//of course, the cost to get to where you start is 0; this prevents going back to origin and makes final path traceback easier.
	Explore(a,b);
}

void graph::Explore(node* current, node* destination){
	if(current==destination){
	//here, we'll have to check to see if we know
	//mathematically that this has to be the minimum path,
	//or if this is the last path in the heap.
	//
	//If it is the minimum or the last path, we'll take the minimum
	//off the heap and use a while loop to follow the path backwards,
	//in the meantime storing each node along this minimum
	//path into our "path" variable as a pointer.
	//Once it reaches the origin (which can be identified by a cost of 0),
	//it will fall out of the while loop
	//and the pointers in the "path" array will be reversed
	//(since we added them in backwards order).
	//(I'm still thinking about the best way to represent the final path)
	}
	else{
		int newcost = current->cost;
		//find edges for node
		for(int i = 0; i < size; i++){
			//check if this spot in the matrix is an existing edge
			if(matrix[current->location][i] >= 0){
				newcost+=matrix[current->location][i];//tentative new cost is current cost + weight of tentative edge
				//if new cost is lower than the current cost to get to tentative location, or if current is -1 (which represents infinity)
				if(newcost < nodes[i].cost || nodes[i].cost < 0)
					Explore(&nodes[i],destination);//Here call Explore recursively on all items that have a smaller cost
			}
		}
	}
}

void graph::InsertEdge(int from, int to, int weight){
	if(from > 0 && from < size && to > 0 && to < size){
		matrix[from][to] = weight;
	}
}
