#ifndef NODE_H
#define NODE_H

struct node{
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in tentative path
    int location;//index of this node on matrix
    
    int x;
    int y;
    char symbol;
};

#endif 
