#include "Simulator.h"

//temporary function for testing
void display(Board** b, Config* p){
	int gens = (p->number_of_generations % p->step == 0) ? p->number_of_generations / p->step : p->number_of_generations / p->step + 1;
	for(int i = 0; i < gens; i++){
		printf("Gen %d:\n", i);
		for(int j = 0; j < b[i]->sizeY; j++){
			for(int k = 0; k < b[i]->sizeX; k++){
				printf("%d ", b[i]->cells[j * b[i]->sizeX + k]);
			}
			printf("\n");
		}
	}
}


CellState* getArea(Board* b, int x, int y){

	CellState* area = malloc (SIZE * sizeof (*area));

	int border = (sqrt(SIZE) - 1) / 2;
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
	Board* result = malloc (sizeof(*result));
	result->sizeX = b->sizeX;
	result->sizeY = b->sizeY;
	result->cells = malloc(result->sizeY * result->sizeX  * sizeof(CellState));

	int iterator = 0;

	for(int j = 0; j < b->sizeY; j++){
		for(int i = 0; i < b->sizeX; i++){
			result->cells[iterator] = nextState(getArea(b, i, j));
			iterator++;
		}
	}
	return result;
}

Board** simulate(Board* b, Config* p){
	int iterator = 0;
	int arraySize = (p->number_of_generations % p->step == 0) ? p->number_of_generations / p->step : p->number_of_generations / p->step + 1;
	Board** boardArray = malloc (sizeof(*boardArray) * arraySize);
	for(int i = 0; i < p->number_of_generations; i++){
		if(i % p->step == 0){
			boardArray[iterator] = b;
			b = nextGen(b);
			iterator++;
		}
	}
	boardArray[p->number_of_generations - 1] = b;
	return boardArray;
}