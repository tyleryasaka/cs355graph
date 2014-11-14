#ifndef BINHEAP_H
#define BINHEAP_H

class binheap {
    private:
        node** heap;
        //double asterisk because this is an array of pointers
		//(pointer to pointers)
        int size;
    public:
        bool Insert(node* n);
        bool Remove(node* n);
        node* Min()const;
};

node* binheap::Min()const{
    if(heap && size > 0)
        return heap[0];
}

#endif
