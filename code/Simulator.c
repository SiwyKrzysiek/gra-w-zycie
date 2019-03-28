#include "Simulator.h"

//temporary function for testing
void display(Board** b, int gens){
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
	}
	return result;
}

Board** simulate(Board* b, Config* p){
	Board** boardArray = malloc (p->number_of_generations * sizeof(Board*));
	for(int i = 0; i < p->number_of_generations; i++){
		b = nextGen(b);
		boardArray[i] = b;
	}
	return boardArray;
}

//testing

int main(){

	Board* b = malloc (sizeof (Board*));
	b->sizeX = 5;
	b->sizeY = 5;
	CellState x[5*5] = {DEAD, ALIVE, DEAD, DEAD, DEAD, 
						DEAD, DEAD, ALIVE, DEAD, DEAD, 
						ALIVE, ALIVE, ALIVE, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD};
	/*CellState x[10*10] = {DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						ALIVE, ALIVE, ALIVE, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD,
						DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD, DEAD};*/
	b->cells = x;
	Config* p = malloc(sizeof (Config*));
	p->number_of_generations = 10;
	p->step = 1;
	p->delay = 200;

	Board** boards = simulate(b, p);
	printf("%d\n", p->number_of_generations);
	display(boards, 10);

	free(p);
	free(b);
	free(boards);



	return 0;
}