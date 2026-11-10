
#include <stdio.h>
#include <assert.h>
#include "priority_queue.h"

int main(void)
{
    Food result;

    printf("\n===== PRIORITY QUEUE / MIN HEAP TESTING =====\n");

    /* TEST 1: Initialization */
    pq_init();
    assert(pq_count() == 0);
    printf("TEST 1 PASSED: Initialization\n");

    /* TEST 2: Empty queue */
    assert(pq_get_urgent(&result) == 0);
    printf("TEST 2 PASSED: Empty queue handling\n");

    /* TEST 3: Priority calculation */
    assert(calculate_priority(1) == 1);
    assert(calculate_priority(4) == 2);
    assert(calculate_priority(8) == 3);
    assert(calculate_priority(15) == 4);
    printf("TEST 3 PASSED: Priority calculation\n");

    /* TEST 4: Insert donations */
    assert(pq_insert(101, 10, 20) == 1);
    assert(pq_insert(102, 2, 15) == 1);
    assert(pq_insert(103, 5, 10) == 1);
    assert(pq_count() == 3);
    printf("TEST 4 PASSED: Donation insertion\n");

    /* TEST 5: Minimum priority retrieval */
    assert(pq_get_urgent(&result) == 1);
    assert(result.donation_id == 102);
    assert(result.priority == 1);
    printf("TEST 5 PASSED: Most urgent donation retrieval\n");

    /* TEST 6: Tie-breaking by expiry */
    pq_init();
    assert(pq_insert(201, 2, 10) == 1);
    assert(pq_insert(202, 1, 10) == 1);
    assert(pq_get_urgent(&result) == 1);
    assert(result.donation_id == 202);
    printf("TEST 6 PASSED: Expiry-based tie-breaking\n");

    /* TEST 7: Tie-breaking by donation ID */
    pq_init();
    assert(pq_insert(205, 2, 10) == 1);
    assert(pq_insert(203, 2, 10) == 1);
    assert(pq_get_urgent(&result) == 1);
    assert(result.donation_id == 203);
    printf("TEST 7 PASSED: Donation ID tie-breaking\n");

    /* TEST 8: Invalid inputs */
    assert(pq_insert(0, 2, 10) == 0);
    assert(pq_insert(301, -1, 10) == 0);
    assert(pq_insert(302, 2, 0) == 0);
    printf("TEST 8 PASSED: Invalid input handling\n");

    /* TEST 9: NULL pointer */
    assert(pq_get_urgent(NULL) == 0);
    printf("TEST 9 PASSED: NULL pointer handling\n");

    /* TEST 10: Display */
    pq_init();
    assert(pq_insert(401, 3, 20) == 1);
    assert(pq_insert(402, 8, 15) == 1);
    printf("\nDisplaying priority queue:\n");
    pq_display();
    printf("TEST 10 PASSED: Queue display\n");

    /* TEST 11: Maximum capacity */
    pq_init();

    for (int i = 1; i <= MAX_FOOD; i++)
        assert(pq_insert(i, 10, 5) == 1);

    assert(pq_count() == MAX_FOOD);
    assert(pq_insert(999, 2, 10) == 0);
    printf("TEST 11 PASSED: Maximum capacity handling\n");

    printf("\n===== ALL PRIORITY QUEUE TESTS PASSED =====\n");

    return 0;
}
