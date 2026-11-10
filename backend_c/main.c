#include <stdio.h>
#include "models.h"
#include "hash_table.h"
#include "bst.h"
#include "sorting.h"
#include "searching.h"
#include "matching.h"
#include "allocation.h"
#include "waste_detection.h"
#include "reprioritization.h"

int main(void) {
    Food food[] = {
        {101, "Rice", "Grains", 100, 5, 70},
        {102, "Milk", "Dairy", 40, 3, 80},
        {103, "Bread", "Bakery", 60, 2, 50},
        {104, "Dal", "Grains", 80, 10, 30},
        {105, "Panner", "Dairy", 50, 2, 90},
        {106, "Biscuits", "Bakery", 70, 1, 40}
    };

    NGO ngos[] = {
        {201, "Helping Hands", "Grains", 50, 100},
        {202, "Food For All", "Dairy", 30, 50},
        {203, "Care Foundation", "Bakery", 40, 70}
    };

    int foodCount = sizeof(food) / sizeof(food[0]);
    int ngoCount = sizeof(ngos) / sizeof(ngos[0]);

    printf("====================================\n");
    printf("   FOOD RESCUE ALGORITHM MODULE\n");
    printf("====================================\n");

    /* 1. Hash Table */
    HashTable ht;
    Donation d1 = {301, 501, 101, 100};
    Donation d2 = {302, 502, 102, 40};

    initHashTable(&ht);
    insertDonation(&ht, d1);
    insertDonation(&ht, d2);
    displayHashTable(&ht);

    Donation *foundDonation = searchDonation(&ht, 301);
    if (foundDonation != NULL)
        printf("Found Donation ID 301, Quantity: %d\n",
               foundDonation->quantity);

    /* 2. BST */
    BSTNode *root = NULL;
    int i;

    for (i = 0; i < foodCount; i++)
        root = insertFood(root, food[i]);

    printf("\n--- BST Inorder ---\n");
    inorderFood(root);

    BSTNode *foundFood = searchFood(root, 103);
    if (foundFood != NULL)
        printf("BST found: %s\n", foundFood->food.name);

    /* 3. Sorting */
    printf("\nBefore sorting:");
    displayFoodList(food, foodCount);

    sortByExpiry(food, foodCount);

    printf("\nSorted by earliest expiry:");
    displayFoodList(food, foodCount);

    /* 4. Searching */
    int index = linearSearchFood(food, foodCount, food[0].id);

    if (index != -1)
        printf("\nSearching: Food found -> %s\n", food[index].name);
    else
        printf("\nFood not found.\n");

    /* 5. Matching */
    Food selectedFood = food[0];
    int bestNGO = findBestNGO(selectedFood, ngos, ngoCount);

    if (bestNGO != -1)
        printf("\nBest NGO for %s: %s\n",
               selectedFood.name, ngos[bestNGO].name);

    /* 6. Fair allocation */
    fairAllocation(100, ngos, ngoCount);

    /* 7. Waste detection */
    printf("\n--- Waste Detection ---\n");
    for (i = 0; i < foodCount; i++)
        displayWasteRisk(food[i]);

    /* 8. Dynamic re-prioritization */
    reprioritizeFood(food, foodCount);
    displayPriority(food, foodCount);

    /* 9. Emergency redistribution */
    printf("\n--- Emergency Redistribution ---\n");
    printf("If an NGO cannot receive food, search another eligible NGO ");
    printf("using the matching algorithm.\n");

    freeBST(root);

    printf("\nAll algorithms executed successfully.\n");

    return 0;
}
