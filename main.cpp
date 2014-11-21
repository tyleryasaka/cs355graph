#include <iostream>
#include "map.h"

int main() {
	
	map parkourMap(30, 30);
	parkourMap.changeSymbol(5, 5, 'H');
	parkourMap.printMap();
}

