#ifndef map_h
#define map_h
#include "graph.h"
#include <iostream>

class map : public graph{
	public:
		//Constructors
		map();
		map(int mapWidth, int mapHeight);
		
		//Mutators
		
		//Accessors
		void printMap();
		
	private:
		int width;
		int height;
		node ***nodeMap;
};

map::map() : width(0), height(0) {}

map::map(int mapWidth, int mapHeight) : graph(mapWidth * mapHeight) {
	width = mapWidth;
	height = mapHeight;
	
	nodeMap = new node**[width];
	for (int i = 0; i < height; i ++)
		nodeMap[i] = new node*[height];
	
	int nodeIndex = 0;
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			nodeMap[w][h] = NodeAccessor(nodeIndex++);
			nodeMap[w][h]->symbol = '0';
			nodeMap[w][h]->x = w;
			nodeMap[w][h]->y = h;
		}
	}
}

void map::printMap() {
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			std::cout << nodeMap[w][h]->symbol;
		}
		std::cout << std::endl;
	}
}


#endif
