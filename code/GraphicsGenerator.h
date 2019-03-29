#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include "Board.h"
#include "gifenc.h"

#define DELAY_IN_MS_BETWEEN_GIF_FRAMES 200

// Saves image representation of given board to specified file
void savePng(Board* board, char* outputFile);

// Saves series of board states into one .gif file
// Each board must have the same size
void saveHistoryAsGif(Board** boards, int numberOfBoards, char* outputFile);