
#include <stdio.h>
#include <string.h>
#include "reprioritization.h"

int main()
{
    Food food[5];
    int i;
    int passed = 0;

    printf("\n===== REPRIORITIZATION TESTING =====\n");

    /* TEST 1: Expiry priority */
    printf("\nTEST 1: Expiry priority calculation\n");

    food[0] = (Food){1, "Rice", "Dry", 20, 1, 10};

    if (calculatePriority(food[0]) == 80) {
        printf("TEST 1 PASSED\n");
        passed++;
    } else {
        printf("TEST 1 FAILED\n");
    }

    /* TEST 2: Demand priority */
    printf("\nTEST 2: Demand priority calculation\n");

    food[0] = (Food){2, "Milk", "Dairy", 10, 10, 25};

    if (calculatePriority(food[0]) == 25) {
        printf("TEST 2 PASSED\n");
        passed++;
    } else {
        printf("TEST 2 FAILED\n");
    }

    /* TEST 3: Extra quantity bonus */
    printf("\nTEST 3: Extra quantity bonus\n");

    food[0] = (Food){3, "Bread", "Bakery", 30, 10, 10};

    if (calculatePriority(food[0]) == 20) {
        printf("TEST 3 PASSED\n");
        passed++;
    } else {
        printf("TEST 3 FAILED\n");
    }

    /* TEST 4: Priority sorting */
    printf("\nTEST 4: Descending priority sorting\n");

    food[0] = (Food){1, "Rice", "Dry", 10, 10, 5};
    food[1] = (Food){2, "Milk", "Dairy", 20, 1, 20};
    food[2] = (Food){3, "Bread", "Bakery", 30, 3, 15};

    reprioritizeFood(food, 3);

    if (calculatePriority(food[0]) >= calculatePriority(food[1]) &&
        calculatePriority(food[1]) >= calculatePriority(food[2])) {
        printf("TEST 4 PASSED\n");
        passed++;
    } else {
        printf("TEST 4 FAILED\n");
    }

    /* TEST 5: Empty array */
    printf("\nTEST 5: Empty array handling\n");

    reprioritizeFood(food, 0);
    displayPriority(food, 0);

    printf("TEST 5 PASSED\n");
    passed++;

    /* TEST 6: Single food item */
    printf("\nTEST 6: Single food item\n");

    food[0] = (Food){4, "Potato", "Vegetable", 15, 5, 10};

    reprioritizeFood(food, 1);

    if (food[0].id == 4) {
        printf("TEST 6 PASSED\n");
        passed++;
    } else {
        printf("TEST 6 FAILED\n");
    }

    /* TEST 7: Display priority */
    printf("\nTEST 7: Priority display\n");

    displayPriority(food, 1);
    printf("TEST 7 PASSED\n");
    passed++;

    printf("\nTOTAL TESTS PASSED: %d/7\n", passed);

    if (passed == 7)
        printf("===== ALL REPRIORITIZATION TESTS PASSED =====\n");

    return 0;
}
