#pragma once

#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "Board.h"
#include "Rules.h"

void testNextStateDeadStaysDead();
void testNextStateDeadComesToLive();
void testNextStateAliveDiesFromOverpopulation();
void testNextStateAliveDiesFromLoneliness();
void testNextStateAliveStaysAlive();