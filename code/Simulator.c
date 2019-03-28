#include "Simulator.h"


CellState* getArea(Board* b, int x, int y){

	CellState* area = malloc (SIZE * sizeof (CellState*));

	int border = (sqrt(SIZE) - 1) / 2; // border = 1, x = 3, y = 0
	int iterator = 0;

	for(int i = y - border; i <= y + border; i++){
		for(int j = x - border; j <= x + border; j++){
			if(j < 0 || j > b->sizeX - 1 || i < 0 || i > b->sizeY - 1)
				area[iterator] = DEAD;
			else area[iterator] = b->cells[i * b->sizeX + j];
			iterator++;
		}
	}

	return area;
}

Board* nextGen(Board* b){

	Board* result = malloc (sizeof (Board*));
	result->sizeX = b->sizeX;
	result->sizeY = b->sizeY;
	result->cells = malloc(SIZE * sizeof(CellState*));

	int iterator = 0;

	for(int j = 0; j < b->sizeY; j++){
		for(int i = 0; i < b->sizeX; i++){
			result->cells[iterator] = nextState(getArea(b, i, j));
			iterator++;
		}
		printf("\n");
	}
	return result;
}

int main(){

	Board* b = malloc (sizeof (Board*));
	b->sizeX = 5;
	b->sizeY = 4;
	CellState x[20] = {ALIVE, DEAD, ALIVE, DEAD, DEAD,
					   DEAD, DEAD, ALIVE, DEAD, ALIVE,
					   DEAD, ALIVE, ALIVE, DEAD, ALIVE,
					   DEAD, DEAD, DEAD, DEAD, DEAD};
	b->cells = x;

	//testing getArea
	/*printf("\ngetArea:\n");	

	CellState* y = malloc (SIZE * sizeof (CellState*));
	y = getArea(b, 2, 0);

	for(int i = 0; i < SIZE; i++)
		printf("%d\n", y[i]);*/

	//testing nextGen
	/*printf("\nnextGen:\n");

	Board* b2 = malloc (sizeof (Board*));
	b2 = nextGen(b);

	for(int i = 0; i < b2->sizeX * b2->sizeY; i++){
		printf("%d\n", b2->cells[i]);
	}*/

	//testing
	/*CellState* a = getArea(b, 3, 0);
	for(int i = 0; i < SIZE; i++){
		printf("%d: %d\n", i, a[i]);
	}

	printf("alive: %d\n", countAlive(a));

	printf("%d\n", nextState(getArea(b,3,0)));*/





	return 0;
}