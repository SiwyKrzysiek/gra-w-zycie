#include "Simulator.h"


int calcHistorySize(Config* config){
	return config->number_of_generations / config->step + 1;
}

//temporary function for testing
void display(Board** b, Config* p){
	int gens = calcHistorySize(p);
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
	result->cells = malloc(result->sizeY * result->sizeX  * sizeof(*(result->cells)));

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
	int arraySize = p->number_of_generations + 1;
	Board** boardArray = malloc (sizeof(*boardArray) * arraySize);
	for(int i = 0; i < p->number_of_generations; i++){
		boardArray[iterator] = b;
		iterator++;
		
		b = nextGen(b);
	}
	boardArray[iterator] = b;
	return boardArray;
}

Board** stepSimulate(Board** board, Config* config){
	int size = (config->number_of_generations + 1) / config->step;
	int iterator = 0;
	Board** result = malloc(sizeof(*result) * size);
	for(int i = 0; i < size; i++){
		result[iterator] = board[i];
		iterator++;
	}
	return result;
}
