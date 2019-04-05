#pragma once

#include <math.h>
#include <stdbool.h>

#include "Board.h"
#include "Rules.h"
#include "ArgumentsParser.h"



void display(Board** b, Config* p);

Board** simulate(Board* b, Config* p);

Board** stepSimulate(Board** b, Config* p);

Board* nextGen(Board* b);

CellState* getArea(Board* b, int x, int y);

int calcHistorySize(Config* c);

