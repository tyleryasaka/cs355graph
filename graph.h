struct node {
    int cost;//total cost to get here from origin of path
    point* prev;//previous node in path
};

class binheap {
    private:
        int* heap;
        int size;
    public:
        bool Insert(node* n);
        bool Remove(node* n);
        node* Min()const;
};

node* binheap::Min(){
    if(heap && size > 0)
        return heap[0];
}
