#pragma once

#include <stdlib.h>
#include <stdio.h> //tests

#include "Board.h"

#define SIZE 9
#define MIDDLE_INDEX 4

CellState nextState(CellState* area);
