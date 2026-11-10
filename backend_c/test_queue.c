
#include <stdio.h>
#include <assert.h>
#include "queue.h"

int main(void)
{
    PickupRequest result;

    printf("\n===== QUEUE TESTING =====\n");

    // Test 1: Initialization
    queue_init();
    assert(queue_count() == 0);
    printf("TEST 1 PASSED: Queue initialization\n");

    // Test 2: Enqueue
    assert(queue_enqueue(101, 201) == 1);
    assert(queue_enqueue(102, 202) == 1);
    assert(queue_enqueue(103, 203) == 1);
    assert(queue_count() == 3);
    printf("TEST 2 PASSED: Enqueue operations\n");

    // Test 3: Display
    printf("\nDisplaying queue:");
    queue_display();

    // Test 4: FIFO order
    assert(queue_dequeue(&result) == 1);
    assert(result.request_id == 101);
    assert(result.donation_id == 201);

    assert(queue_dequeue(&result) == 1);
    assert(result.request_id == 102);
    assert(result.donation_id == 202);

    printf("\nTEST 3 PASSED: FIFO order\n");

    // Test 5: Remaining element
    assert(queue_dequeue(&result) == 1);
    assert(result.request_id == 103);
    assert(result.donation_id == 203);
    assert(queue_count() == 0);

    printf("TEST 4 PASSED: Dequeue operations\n");

    // Test 6: Empty queue
    assert(queue_dequeue(&result) == 0);
    printf("TEST 5 PASSED: Empty queue handling\n");

    // Test 7: Invalid input
    assert(queue_enqueue(0, 201) == 0);
    assert(queue_enqueue(101, -1) == 0);
    printf("TEST 6 PASSED: Invalid input handling\n");

    // Test 8: Maximum capacity
    queue_init();

    for (int i = 1; i <= MAX_REQUESTS; i++)
    {
        assert(queue_enqueue(i, i + 1000) == 1);
    }

    assert(queue_count() == MAX_REQUESTS);
    assert(queue_enqueue(999, 999) == 0);

    printf("TEST 7 PASSED: Maximum capacity handling\n");

    // Test 9: Circular queue operation
    for (int i = 0; i < 50; i++)
    {
        assert(queue_dequeue(&result) == 1);
    }

    for (int i = 101; i <= 150; i++)
    {
        assert(queue_enqueue(i, i + 1000) == 1);
    }

    assert(queue_count() == MAX_REQUESTS);

    printf("TEST 8 PASSED: Circular queue operation\n");

    printf("\n===== ALL QUEUE TESTS PASSED =====\n");

    return 0;
}
