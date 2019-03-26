#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include "Board.h"

// Saves image representation of given board to specified file
void savePng(Board* board, char* outputFile);