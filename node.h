#ifndef NODE_H
#define NODE_H

struct node{
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in tentative path
    int location;//index of this node on matrix
    node operator=(const node &n);
};

node node::operator=(const node &n){
	cost = n.cost;
	prev = n.prev;
	location = n.location;
	return *this;
}

#endif 
