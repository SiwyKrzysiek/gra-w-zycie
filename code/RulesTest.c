#include "RulesTest.h"

void testNextStateDeadStaysDead()
{
    //Given
    CellState states[] = {ALIVE, ALIVE, DEAD,
                          ALIVE, DEAD, ALIVE,
                          DEAD, ALIVE, DEAD};
    CellState *area = malloc(SIZE * sizeof(*area));
    memcpy(area, states, SIZE * sizeof(*area));

    //When
    CellState futureState = nextState(area);

    //Then
    CU_ASSERT_EQUAL(futureState, DEAD);
}

void testNextStateDeadComesToLive()
{
    //Given
    CellState states[] = {ALIVE, ALIVE, DEAD,
                          DEAD, DEAD, DEAD,
                          DEAD, ALIVE, DEAD};
    CellState *area = malloc(SIZE * sizeof(*area));
    memcpy(area, states, SIZE * sizeof(*area));

    //When
    CellState futureState = nextState(area);

    //Then
    CU_ASSERT_EQUAL(futureState, ALIVE);
}

void testNextStateAliveDiesFromOverpopulation()
{
    //Given
    CellState states[] = {ALIVE, ALIVE, DEAD,
                          ALIVE, ALIVE, DEAD,
                          ALIVE, ALIVE, DEAD};
    CellState *area = malloc(SIZE * sizeof(*area));
    memcpy(area, states, SIZE * sizeof(*area));

    //When
    CellState futureState = nextState(area);

    //Then
    CU_ASSERT_EQUAL(futureState, DEAD);
}

void testNextStateAliveDiesFromLoneliness()
{
    //Given
    CellState states[] = {DEAD, DEAD, DEAD,
                          DEAD, ALIVE, DEAD,
                          ALIVE, DEAD, DEAD};
    CellState *area = malloc(SIZE * sizeof(*area));
    memcpy(area, states, SIZE * sizeof(*area));

    //When
    CellState futureState = nextState(area);

    //Then
    CU_ASSERT_EQUAL(futureState, DEAD);
}