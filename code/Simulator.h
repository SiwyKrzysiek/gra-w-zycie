#pragma once

#include <math.h>

#include "Board.h"
#include "Rules.h"
#include "ArgumentsParser.h"


#define clear() printf("\033[H\033[J") //clearing terminal

void display(Board** b, int gens);

Board** simulate(Board* b, Config* p);

Board* nextGen(Board* b);

CellState* getArea(Board* b, int x, int y);

