#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

typedef struct
{
    int lastLineReadNumber;
    int lastCharacterReadNumber;
} ParseInformation;

//Stores data about parsing process. Can be used to identify where erros coured.
ParseInformation PARSE_INFORMATION;

//Parses a file to a Board struct
Board loadBoardFromFile(const char* fileName);