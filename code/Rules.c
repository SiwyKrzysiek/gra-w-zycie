#include "Rules.h"

int countAlive(CellState* area){
	int counter = 0;
	for(int i = 0; i < SIZE; i++){
		if(i != 4 && area[i] == ALIVE) counter++;
	}
	return counter;
}

CellState nextState(CellState* area){
	int alive = countAlive(area);
	if (area[MIDDLE_INDEX] == DEAD && alive == 3) return ALIVE;
	else if (area[MIDDLE_INDEX] == ALIVE && (alive != 3 || alive != 2)) return DEAD;
	return area[MIDDLE_INDEX];
}
