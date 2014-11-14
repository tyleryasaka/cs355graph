class binheap;

struct node {
	friend class binheap;
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in path
};

#include "binheap.h"

