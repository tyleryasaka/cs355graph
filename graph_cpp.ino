struct node{
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in tentative path
    int location;//index of this node on matrix
};

struct path{
	int length;
	int* location;
	path():length(0),location(0){}
	path(int l){
		length = l;
		location = new int[length];
	}
	path(const path& source){
		length = source.length;
		location = new int[length];
		for(int i=0;i<length;i++)
			location[i] = source.location[i];
	}
	path& operator =(const path& source){
		delete[] location;
		length = source.length;
		location = new int[length];
		for(int i=0;i<length;i++)
			location[i] = source.location[i];
		return *this;
	}
	~path(){
		delete[] location;
		location = 0;
		length = 0;
	}
};

class binheap {
    private:
		//the heap:
        //double asterisk because this is an array of pointers
		//(pointer to pointers)
        node** heap;
        int size;//size of heap
        int last;//index of last item in heap
        void SwapNode(int i, int j);
        void Copy(const binheap& source);//Helper for copy constructor/assignment operator
    public:
		binheap():heap(0),size(0),last(-1){};
		binheap(int heap_size);
		binheap(const binheap& source);
		binheap& operator=(const binheap& source);
		~binheap();
        void Insert(node* n);
        node* Remove();
        node* Min()const;
        bool empty();
};

//swaps nodes in heap at given indeces
void binheap::SwapNode(int i, int j){
	node* temp = heap[i];
	heap[i] = heap [j];
	heap[j] = temp;
}

void binheap::Copy(const binheap& source){
	size = source.size;
	last = source.last;
	heap = new node*[size];
	for(int i=0;i<size;i++){
		heap[i] = source.heap[i];
	}
}

binheap::binheap(const binheap& source){
	Copy(source);
}

binheap& binheap::operator=(const binheap& source){
	delete[] heap;
	Copy(source);
	return *this;
}

//overloaded constructor
binheap::binheap(int heap_size){
	if (heap_size < 0){
		heap = 0;
		size = 0;
	}
	else {
		size = heap_size;
		heap = new node*[size];
	}
	last = -1;
}

binheap::~binheap(){
	delete[] heap;
	heap = 0;
}

//returns item at top of heap
node* binheap::Min()const{
    if(heap && size > 0)
        return heap[0];
    else
		return 0;
}

//inserts an item into heap, maintaining heap property (parent <= children)
void binheap::Insert(node* n){
	bool done = false;
	int current = last + 1;//item will start at bottom of heap
	int parent = 0;//keeps track of index of parent node
	//1. start by inserting item at bottom of heap
	heap[current] = n;//inserts item at bottom of heap
	last++;//update location of last item
	//2. Swap with parent until it is larger than parent
	//or it becomes root (current==0)
	while(current > 0 && !done){
		//identify parent
		if(current%2==0)//if index is even, this is a right child or root
			parent = (current-2)/2;
		else//if index is odd
			parent = (current-1)/2;
		if(heap[current]->cost<heap[parent]->cost){//if item is smaller than parent
			SwapNode(current,parent);//swap values in item and parent
			current = parent;//now our item is at parent spot, so we need to keep up with it
		}
		else//item is greater than or equal to parent (what we want)
			done = true;//fall out of the loop
	}
}

node* binheap::Remove(){
	node* result = 0;
	if(last>=0){
		bool done = false;
		result = heap[0];//pass node pointer to variable to be returned
		heap[0] = heap[last];//Place last item at top of heap
		heap[last] = 0;//Remove the last item from former location
		last--;//Now last item is one lower in heap
		int current = 0;//keeps track of the location of node we are moving
		int left = 0;//var for left child
		int right = 0;//var for right child
		int minchild = 0;//temp variable for comparing children
		while(!done){
			left = current*2+1;
			right = current*2+2;
			if(left <= last){//if it has a left child
				if(right <= last){//if it has a right child
					if(heap[left]->cost < heap[right]->cost)//find which child is smaller
						minchild = left;
					else
						minchild = right;
					if(heap[minchild]->cost < heap[current]->cost){//compare current with smallest child
						SwapNode(current,minchild);
						current = minchild;
					}
					else//if smaller child is not smaller than current, we're done
						done = true;
				}
				else if(heap[left]->cost < heap[current]->cost){//if left less than current, swap
					SwapNode(current, left);
					current = left;//our current node is now where left was
				}
				else
					done = true;//if left but no right and left not less than current, we're done
			}
			else//if no left child, can't have right child, so we're done
				done = true;
		}
	}
	return result;
}

//sees if heap is empty by where the last index is
bool binheap::empty(){
	return (last == -1);
}

//---------------------------------------------------------------------
//Graph
//---------------------------------------------------------------------

class graph{
	private:
		int size;   //nodes in graph
		node* nodes;//container for all nodes in graph
		int** matrix;
		binheap* heap;//choose a better name?
		void Copy(const graph& source);//Helper for copy constructor/assignment operator
		void ClearPath();//Resets nodes' prev and cost but not location
	public:
		graph():size(0){};
		graph(int graph_size);
		graph(const graph& source);
		graph& operator=(const graph& source);
		~graph();
		path ShortestPath(int A, int B);
		void InsertEdge(int from, int to, int weight); //This also updates existing edges
		void ClearEdge(int from, int to);//removes a single matrix spot
		void ClearEdges();//resets entire matrix
};

void graph::Copy(const graph& source){
	size = source.size;
	nodes = new node[size];
	matrix = new int*[size];
	for(int i=0;i<size;i++){
		nodes[i] = source.nodes[i];
		matrix[i] = source.matrix[i];
	}
	heap = new binheap(size);
	*heap = *source.heap;
}

void graph::ClearPath(){
	for(int i=0;i<size;i++){
		nodes[i].cost = -1;
		nodes[i].prev = 0;
	}
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

graph::graph(const graph& source){
	Copy(source);
}

graph& graph::operator=(const graph& source){
	delete nodes;
	delete matrix;
	delete heap;
	Copy(source);
	return *this;
}

graph::~graph(){
	delete nodes;
	delete matrix;
	delete heap;
	nodes = 0;
	matrix = 0;
	heap = 0;
}

//input: indeces of nodes in matrix for begin and end point of desired path
//output: for now, array of indeces could be set to object's "path" array for shortest path... maybe change to LinkedList?
path graph::ShortestPath(int start,int end){
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
	int* backtrack = new int[size];//This is where we'll store the final path
	int pathlen = 0;
	while(current != start){//when current is beginning
		backtrack[pathlen] = current;
		pathlen++;
		current = nodes[current].prev->location;
	}
	backtrack[pathlen] = start;//Don't forget to include the first node!
	pathlen++;
	
	path returnPath(pathlen);
	for(int i=0;i<pathlen;i++){
		returnPath.location[i] = backtrack[(pathlen-i-1)];
	}
	
	ClearPath();//Clear the path made from the graph
	
	return returnPath;
}

void graph::InsertEdge(int from, int to, int weight){
	if(from >= 0 && from < size && to >= 0 && to < size){
		matrix[from][to] = weight;
	}
}

//-------------------------------------------------------------------------------

// constants won't change. Used here to 
// set pin numbers:
int lights[] = {11,8,4,9,5,2,10,6,7,3};

void setup() {
  // set the digital pin as output:
  for(int i;i<10;i++)
    pinMode(lights[i], OUTPUT);
}

void ResetLights(){
  for(int i;i<10;i++)
    digitalWrite(lights[i],HIGH);   
}

void loop()
{
	ResetLights();
	
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
	
	delay(1000);
	
	for(int i=0;i<route.length;i++){
		digitalWrite(lights[route.location[i]],LOW);
        delay(1000);
	}

    delay(5000);
}

