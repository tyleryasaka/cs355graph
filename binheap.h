#ifndef BINHEAP_H
#define BINHEAP_H

class binheap {
    private:
		//the heap:
        //double asterisk because this is an array of pointers
		//(pointer to pointers)
        node** heap;
        int size;//size of heap
        int last;//index of last item in heap
        void SwapNode(int i, int j);
    public:
		binheap():heap(0),size(0),last(-1){};
		binheap(int heap_size);
        void Insert(node* n);
        void Remove(node* n);
        node* Min()const;
};

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

//swaps nodes in heap at given indeces
void binheap::SwapNode(int i, int j){
	node* temp = heap[i];
	heap[i] = heap [j];
	heap[j] = temp;
}

#endif
