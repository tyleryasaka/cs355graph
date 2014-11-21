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
		
		node ***nodeMap; //Needs accessor function
	private:
		int width;
		int height;
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
			nodeMap[w][h] = NodeAccessor(nodeIndex);
			nodeMap[w][h]->location = nodeIndex;
			nodeMap[w][h]->x = w;
			nodeMap[w][h]->y = h;
			nodeIndex++;
			nodeMap[w][h]->symbol = '^';
		}
	}
	for (int h = height - 1; h >= 0; h--) {
		for (int w = width - 1; w >= 0; w--) {
			if ((w + 1 == width) && (h != 0)) { //Right edge and not bordering the top
				InsertEdge(nodeMap[w][h]->location, nodeMap[w - 1][h]->location, 1); //Connect to left node
				InsertEdge(nodeMap[w][h]->location, nodeMap[w][h - 1]->location, 1); // Connect to above node
			}
			else if ((w + 1 == width) && (h == 0)) { //Right edge and bordering the top
				InsertEdge(nodeMap[w][h]->location, nodeMap[w - 1][h]->location, 1); //Connect to left node
			}
			else if ((w == 0) && (h != 0)) { //Left edge and not bordering the top
				InsertEdge(nodeMap[w][h]->location, nodeMap[w + 1][h]->location, 1); //Connect to right node
				InsertEdge(nodeMap[w][h]->location, nodeMap[w][h - 1]->location, 1); //Connect to above node
			}
			else if ((w == 0) && (h == 0)) { //Left edge and bordering the top
				InsertEdge(nodeMap[w][h]->location, nodeMap[w + 1][h]->location, 1); //Connect to right node
			}
			else if (h == 0) { //Bordering the top
				InsertEdge(nodeMap[w][h]->location, nodeMap[w - 1][h]->location, 1); //Connect to left node
				InsertEdge(nodeMap[w][h]->location, nodeMap[w + 1][h]->location, 1); //Connect to right node
			}
			else { //Not bordering the left, right, or top
				InsertEdge(nodeMap[w][h]->location, nodeMap[w - 1][h]->location, 1); //Connect to left node
				InsertEdge(nodeMap[w][h]->location, nodeMap[w + 1][h]->location, 1); //Connect to right node
				InsertEdge(nodeMap[w][h]->location, nodeMap[w][h - 1]->location, 1); // Connect to above node								
			}
		}
	}
}

void map::printMap() {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			std::cout << nodeMap[w][h]->symbol;
		}
		std::cout << std::endl;
	}
}

void map::changeSymbol(int xVal, int yVal, char newSymbol) {
	nodeMap[xVal][yVal]->symbol = newSymbol;
}


#endif
