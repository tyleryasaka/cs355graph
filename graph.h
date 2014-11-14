#include <vector>
#include "binheap.h"
using namespace std;

class binheap;

struct node {
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in tentative path
    int location;//index of this node on matrix
    node operator=(const node &n);
};



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
		void ShortestPath(int A, int B);
		void InsertEdge(int from, int to, int weight); //This also updates existing edges
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
void graph::ShortestPath(int A,int B){
	int current = A;
	node* currentNode = nodes[current];
	int end = B;
	heap.insert(currentNode);

	while(!heap.Empty() && !heap.Root(nodes[end])){        //root method will take a node as a parameter and determine if that node is the root
														//if end holds the smallest value in heap you know you reached the shortest path because  											//all other nodes are further from the orgin
		for(int i=0; i< size; i++){
			if(matrix[current][i] != -1){      			//if there's a connection
				if(nodes[current]->cost + matrix[current][i] < nodes[i]->cost) || (nodes[i]->cost == -1)){   //if the eye's distance from orgin + endgelength  less than tentative node distance
						nodes[i]->cost = nodes[current]->cost + matrix[current][i];
						nodes[i]->previous = currentNode;
						heap.Insert(nodes[i]);
				}
				//if the path is not shorter nothing changes
			}
		}

		currentNode = heap.Remove();              
		for( int i = 0; i < size; i++){
			if(currentNode == nodes[i]){  	//linear search to find index corresponding to the node
				current = i;         		//changes the eye
				break;
			}             
		}
	}


	//after above while loop has run we will start at the end and trace our way back pushing nodes onto a stack. we will return the stack
	//and the user can pop off nodes to find the path
		
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
