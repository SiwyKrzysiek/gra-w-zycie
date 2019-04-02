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
	CellState result = DEAD;

	if (area[MIDDLE_INDEX] == DEAD && alive == 3) result = ALIVE;
	else if (area[MIDDLE_INDEX] == ALIVE && alive != 3 && alive != 2) result =  DEAD;
	result = area[MIDDLE_INDEX];

	free(area);
	return result;
}
