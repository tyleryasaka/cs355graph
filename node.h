#ifndef NODE_H
#define NODE_H

struct node{
    int cost;//total cost to get here from origin of path
    node* prev;//previous node in tentative path
    int location;//index of this node on matrix
    
    //x & y are used for integration with the path class
    int x; //Allows node to refer back to a grid location on the map
    int y; //Allows node to refer back to a grid location on the map
    
	char symbol; //Symbols are customizable for mapping
};

#endif 
