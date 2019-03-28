#include "Simulator.h"

//temporary function for testing
void display(Board* b){
	printf("\n\n\n");
	for(int i = 0; i < b->sizeY; i++){
		for(int j = 0; j < b->sizeX; j++){
			printf("%d ", b->cells[i * b->sizeX + j]);
		}
		printf("\n");
	}
}


CellState* getArea(Board* b, int x, int y){

	CellState* area = malloc (SIZE * sizeof (CellState*));

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

Board* simulate(Board* b, Config* p){
	for(int i = 0; i < p->number_of_generations; i++){
		clear();
		if(i % p->step == 0) display(b);
		b = nextGen(b);
		usleep(p->delay * 1000);
	}
	return b;
}

//testing

int main(){

	Board* b = malloc (sizeof (Board*));
	b->sizeX = 7;
	b->sizeY = 7;
	CellState x[7*7] = {DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, 
						DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, 
						ALIVE, ALIVE, ALIVE, DEAD, DEAD, DEAD, DEAD, 
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD};
	b->cells = x;

	Config* p = malloc(sizeof (Config*));
	p->number_of_generations = 20;
	p->step = 1;
	p->delay = 200;

	simulate(b, p);

	free(p);
	free(b);



	return 0;
}