#pragma once

#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "Board.h"
#include "BoardHandler.h"
#include "Simulator.h"

//Test simulator on case from documentation
void testSimulateOneNextGenOnSmallBoard();
void testSimulateTenNextGenOnNotSoSmallBoard();