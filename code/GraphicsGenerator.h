#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include <math.h>
#include "Board.h"
#include "gifenc.h"

#define MIN_IMAGE_SIZE 600//Used for image upscaling
typedef int Pixel;

// Saves image representation of given board to specified file
void savePng(Board* board, char* outputFile);

// Saves series of board states into one .gif file
// Each board must have the same size
void saveHistoryAsGif(Board** boards, int numberOfBoards, char* outputFile, int delay);

// Creates upscaled version of given image
// At the longest dimension
// Upscaled image size is written to newX and newY arguents
// Returned array must be feed
Pixel* upscaleImage(const Pixel* original, int imageX, int imageY, int* newX, int* newY);