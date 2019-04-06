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