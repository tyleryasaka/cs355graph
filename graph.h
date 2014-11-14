#include <vector>
using namespace std;

class binheap;

struct node {
	friend class binheap;
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in path
};

#include "binheap.h"

class graph{
	private:
		vector<node>* edges;
		binheap heap;//choose a better name?
	public:
		
};
