#include <iostream>
#include "map.h"



int main() {
	
	map parkourMap(5, 5);
	
	path route = parkourMap.ShortestPath(14, 0);
	
	for(int i=0;i<route.length;i++){
		parkourMap.changeSymbol(parkourMap.NodeAccessor(route.location[i])->x, parkourMap.NodeAccessor(route.location[i])->y, 'T');
		parkourMap.printMap();
		std::cout << std::endl;
	}

	
	return 0;
}


