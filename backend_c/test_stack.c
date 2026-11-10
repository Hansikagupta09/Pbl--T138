
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main(void)
{
    Action result;

    printf("\n===== STACK TESTING =====\n");

    // Test 1: Initialization
    stack_init();
    assert(stack_count() == 0);
    printf("TEST 1 PASSED: Stack initialization\n");

    // Test 2: Push operations
    assert(stack_push(101, 201) == 1);
    assert(stack_push(102, 202) == 1);
    assert(stack_push(103, 203) == 1);
    assert(stack_count() == 3);
    printf("TEST 2 PASSED: Push operations\n");

    // Test 3: Display stack
    printf("\nDisplaying stack:");
    stack_display();

    // Test 4: LIFO order
    assert(stack_pop(&result) == 1);
    assert(result.action_id == 103);
    assert(result.donation_id == 203);

    assert(stack_pop(&result) == 1);
    assert(result.action_id == 102);
    assert(result.donation_id == 202);

    printf("\nTEST 3 PASSED: LIFO order\n");

    // Test 5: Remaining element
    assert(stack_pop(&result) == 1);
    assert(result.action_id == 101);
    assert(result.donation_id == 201);
    assert(stack_count() == 0);

    printf("TEST 4 PASSED: Pop operations\n");

    // Test 6: Empty stack handling
    assert(stack_pop(&result) == 0);
    printf("TEST 5 PASSED: Empty stack handling\n");

    // Test 7: Invalid input handling
    assert(stack_push(0, 201) == 0);
    assert(stack_push(101, -1) == 0);
    printf("TEST 6 PASSED: Invalid input handling\n");

    // Test 8: Maximum capacity
    stack_init();

    for (int i = 1; i <= MAX_ACTIONS; i++)
    {
        assert(stack_push(i, i + 1000) == 1);
    }

    assert(stack_count() == MAX_ACTIONS);
    assert(stack_push(999, 999) == 0);

    printf("TEST 7 PASSED: Maximum capacity handling\n");

    // Test 9: Stack after removing elements
    for (int i = 0; i < 50; i++)
    {
        assert(stack_pop(&result) == 1);
    }

    for (int i = 101; i <= 150; i++)
    {
        assert(stack_push(i, i + 1000) == 1);
    }

    assert(stack_count() == MAX_ACTIONS);

    printf("TEST 8 PASSED: Stack reuse after pop\n");

    // Test 10: NULL pointer handling
    assert(stack_pop(NULL) == 0);
    printf("TEST 9 PASSED: NULL pointer handling\n");

    printf("\n===== ALL STACK TESTS PASSED =====\n");

    return 0;
}
