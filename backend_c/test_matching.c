
#include <stdio.h>
#include <string.h>
#include "matching.h"

int main()
{
    Food food;
    NGO ngos[3];
    int result;

    printf("\n===== NGO MATCHING TESTING =====\n");

    /* TEST 1: Exact food type match */
    printf("\nTEST 1: Exact food type match\n");

    strcpy(food.type, "Rice");
    food.quantity = 20;

    ngos[0] = (NGO){1, "NGO_A", "Rice", 10, 30};
    ngos[1] = (NGO){2, "NGO_B", "Milk", 10, 30};

    result = findBestNGO(food, ngos, 2);

    if (result == 0)
        printf("TEST 1 PASSED\n");
    else
        printf("TEST 1 FAILED\n");

    /* TEST 2: Quantity requirement satisfied */
    printf("\nTEST 2: Quantity requirement\n");

    strcpy(food.type, "Rice");
    food.quantity = 20;

    ngos[0] = (NGO){1, "NGO_A", "Rice", 10, 30};
    ngos[1] = (NGO){2, "NGO_B", "Rice", 30, 30};

    result = findBestNGO(food, ngos, 2);

    if (result == 0)
        printf("TEST 2 PASSED\n");
    else
        printf("TEST 2 FAILED\n");

    /* TEST 3: Capacity consideration */
    printf("\nTEST 3: Capacity consideration\n");

    strcpy(food.type, "Rice");
    food.quantity = 20;

    ngos[0] = (NGO){1, "NGO_A", "Rice", 10, 10};
    ngos[1] = (NGO){2, "NGO_B", "Rice", 10, 30};

    result = findBestNGO(food, ngos, 2);

    if (result == 1)
        printf("TEST 3 PASSED\n");
    else
        printf("TEST 3 FAILED\n");

    /* TEST 4: No matching food type */
    printf("\nTEST 4: No matching food type\n");

    strcpy(food.type, "Bread");
    food.quantity = 10;

    ngos[0] = (NGO){1, "NGO_A", "Rice", 50, 20};
    ngos[1] = (NGO){2, "NGO_B", "Milk", 50, 20};

    result = findBestNGO(food, ngos, 2);

    if (result >= 0 && result < 2)
        printf("TEST 4 PASSED: Best available score returned\n");
    else
        printf("TEST 4 FAILED\n");

    /* TEST 5: Empty NGO list */
    printf("\nTEST 5: Empty NGO list\n");

    result = findBestNGO(food, ngos, 0);

    if (result == -1)
        printf("TEST 5 PASSED\n");
    else
        printf("TEST 5 FAILED\n");

    /* TEST 6: Single NGO */
    printf("\nTEST 6: Single NGO\n");

    ngos[0] = (NGO){1, "NGO_A", "Bread", 5, 20};

    result = findBestNGO(food, ngos, 1);

    if (result == 0)
        printf("TEST 6 PASSED\n");
    else
        printf("TEST 6 FAILED\n");

    printf("\n===== MATCHING TESTING COMPLETED =====\n");

    return 0;
}
