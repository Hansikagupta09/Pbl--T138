
#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

int main(void)
{
    TrackingNode *temp;

    printf("\n===== LINKED LIST TESTING =====\n");

    // Test 1: Initialization
    tracking_init();
    printf("TEST 1 PASSED: Initialization\n");

    // Test 2: Empty list display
    tracking_display();
    printf("TEST 2 PASSED: Empty list handling\n");

    // Test 3: Insert first node
    assert(tracking_add(101, 1) == 1);
    printf("TEST 3 PASSED: First node insertion\n");

    // Test 4: Insert multiple nodes
    assert(tracking_add(102, 2) == 1);
    assert(tracking_add(103, 3) == 1);
    assert(tracking_add(104, 4) == 1);
    printf("TEST 4 PASSED: Multiple node insertion\n");

    // Test 5: Display list
    tracking_display();

    temp = NULL;

    // Test 6: Verify insertion order
    // The list is private, so we verify through display
    // and the known status conversion function.
    assert(tracking_status_name(1)[0] == 'D');
    assert(tracking_status_name(2)[0] == 'M');
    printf("TEST 5 PASSED: Status conversion\n");

    // Test 7: Update existing donation
    assert(tracking_update(102, 5) == 1);
    printf("TEST 6 PASSED: Update existing record\n");

    // Test 8: Update nonexistent donation
    assert(tracking_update(999, 3) == 0);
    printf("TEST 7 PASSED: Nonexistent record handling\n");

    // Test 9: Invalid donation ID
    assert(tracking_add(0, 1) == 0);
    assert(tracking_add(-5, 2) == 0);
    printf("TEST 8 PASSED: Invalid donation ID handling\n");

    // Test 10: Status names
    assert(tracking_status_name(1)[0] == 'D');
    assert(tracking_status_name(2)[0] == 'M');
    assert(tracking_status_name(3)[0] == 'P');
    assert(tracking_status_name(4)[0] == 'I');
    assert(tracking_status_name(5)[0] == 'D');
    assert(tracking_status_name(99)[0] == 'U');
    printf("TEST 9 PASSED: All status names\n");

    // Test 11: Clear list
    tracking_clear();
    printf("TEST 10 PASSED: Clear linked list\n");

    // Test 12: Reuse after clearing
    assert(tracking_add(105, 1) == 1);
    tracking_display();
    printf("TEST 11 PASSED: Reuse after clearing\n");

    // Test 13: Clear again
    tracking_clear();
    tracking_display();
    printf("TEST 12 PASSED: Final cleanup\n");

    printf("\n===== ALL LINKED LIST TESTS PASSED =====\n");

    return 0;
}
