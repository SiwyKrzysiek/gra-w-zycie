#include "Simulator.h"


CellState* getArea(Board* b, int x, int y){

	CellState* area;

	area[MIDDLE_INDEX] = b->cells[y * b->sizeX + x];

	int border = (sqrt(SIZE) - 1) / 2;

	for(int i = x - border; i < sqrt(SIZE); i++){
		for(int j = y - border; j < sqrt(SIZE); j++){
			if(x + i < 0 || x + i > b->sizeX - 1 || y + j < 0 || y + j > b->sizeX - 1)
				area[i * b->sizeX + j] = DEAD;
			else area[i * b->sizeX + j] = b->cells[i * b->sizeX + j];
		}
	}
	
	return area;
}

int main(){

	Board* b;
	b->sizeX = 5;
	b->sizeY = 4;
	CellState x[20] = {ALIVE, ALIVE, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD};
	b->cells = x;

	CellState* y = getArea(b, 1, 1);

	for(int i = 0; i < SIZE; i++){
		printf("%d\n", x[i]);
	}

	return 0;
}