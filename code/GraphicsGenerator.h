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

#define MIN_IMAGE_SIZE 600 //Used for image upscaling
typedef int Pixel;

// Saves image representation of given board to specified file
void savePng(Board *board, char *outputFile);

// Saves series of board states into one .gif file
// Each board must have the same size
void saveHistoryAsGif(Board **boards, int numberOfBoards, char *outputFile, int delay);

// Changes board object to Pixel array as instructed by valueOfAlive, valueOfDead
// Each ALIVE cell will have Pixel value of valueOfAlive
// Each DEAD cell will have Pixel value of valueOfDead
// // Returned array must be freed
Pixel *translateBoardToPixels(Board *board, Pixel valueOfAlive, Pixel valueOfDead);

// Calculates size of upscaled image
// Results are put to variables pointed by newX and newY
void getUpscaledImageSize(int orginalX, int orginalY, int *newX, int *newY);

// Creates upscaled version of given image
// Longest edge determines size
// Returned array must be freed
Pixel *upscaleImage(const Pixel *original, int imageX, int imageY);