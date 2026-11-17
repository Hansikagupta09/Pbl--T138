
#include <stdio.h>
#include "waste_detection.h"

int main()
{
    Food food;
    int score;
    int passed = 0;

    printf("\n===== WASTE DETECTION TESTING =====\n");

    /* TEST 1: Food expiring within one day */
    printf("\nTEST 1: Expiry within one day\n");

    food = (Food){1, "Milk", "Dairy", 10, 1, 10};
    score = calculateWasteRisk(food);

    if (score == 60) {
        printf("TEST 1 PASSED\n");
        passed++;
    } else {
        printf("TEST 1 FAILED: Score = %d\n", score);
    }

    /* TEST 2: Food expiring within three days */
    printf("\nTEST 2: Expiry within three days\n");

    food = (Food){2, "Bread", "Bakery", 10, 3, 10};
    score = calculateWasteRisk(food);

    if (score == 40) {
        printf("TEST 2 PASSED\n");
        passed++;
    } else {
        printf("TEST 2 FAILED: Score = %d\n", score);
    }

    /* TEST 3: Food expiring within seven days */
    printf("\nTEST 3: Expiry within seven days\n");

    food = (Food){3, "Rice", "Dry", 10, 7, 10};
    score = calculateWasteRisk(food);

    if (score == 20) {
        printf("TEST 3 PASSED\n");
        passed++;
    } else {
        printf("TEST 3 FAILED: Score = %d\n", score);
    }

    /* TEST 4: Excess quantity */
    printf("\nTEST 4: Excess quantity risk\n");

    food = (Food){4, "Potato", "Vegetable", 30, 10, 10};
    score = calculateWasteRisk(food);

    if (score == 30) {
        printf("TEST 4 PASSED\n");
        passed++;
    } else {
        printf("TEST 4 FAILED: Score = %d\n", score);
    }

    /* TEST 5: Very high waste risk */
    printf("\nTEST 5: High waste risk\n");

    food = (Food){5, "Milk", "Dairy", 30, 1, 10};
    score = calculateWasteRisk(food);

    if (score == 90) {
        printf("TEST 5 PASSED\n");
        passed++;
    } else {
        printf("TEST 5 FAILED: Score = %d\n", score);
    }

    /* TEST 6: Low waste risk */
    printf("\nTEST 6: Low waste risk\n");

    food = (Food){6, "Rice", "Dry", 5, 15, 10};
    score = calculateWasteRisk(food);

    if (score == 0) {
        printf("TEST 6 PASSED\n");
        passed++;
    } else {
        printf("TEST 6 FAILED: Score = %d\n", score);
    }

    /* TEST 7: Waste risk display */
    printf("\nTEST 7: Waste risk display\n");

    food = (Food){7, "Milk", "Dairy", 30, 1, 10};
    displayWasteRisk(food);

    printf("TEST 7 PASSED: Display function executed\n");
    passed++;

    printf("\nTOTAL TESTS PASSED: %d/7\n", passed);

    if (passed == 7)
        printf("===== ALL WASTE DETECTION TESTS PASSED =====\n");

    return 0;
}
