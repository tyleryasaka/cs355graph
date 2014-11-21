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
		void changeSymbol(int xVal, int yVal, char newSymbol);
		
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
			if ((w == 0 || h ==  0) || (w == width - 1 || h == height - 1)) {
				nodeMap[w][h]->symbol = '#';
			}
			else 
				nodeMap[w][h]->symbol = 0;
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

void map::changeSymbol(int xVal, int yVal, char newSymbol) {
	nodeMap[xVal][yVal]->symbol = newSymbol;
}


#endif
