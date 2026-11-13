#include <stdio.h>
#include "sorting.h"

static void swapFood(Food *a, Food *b) {
    Food temp = *a;
    *a = *b;
    *b = temp;
}

void sortByExpiry(Food food[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (food[j].days_to_expire > food[j + 1].days_to_expire)
                swapFood(&food[j], &food[j + 1]);
        }
    }
}

void sortByQuantity(Food food[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (food[j].quantity < food[j + 1].quantity)
                swapFood(&food[j], &food[j + 1]);
        }
    }
}

void sortByDemand(Food food[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (food[j].demand < food[j + 1].demand)
                swapFood(&food[j], &food[j + 1]);
        }
    }
}

void displayFoodList(Food food[], int n) {
    int i;
    printf("\n--- Food List ---\n");
    for (i = 0; i < n; i++) {
        printf("ID: %d | %s | Type: %s | Qty: %d | Expiry: %d days | Demand: %d\n",
               food[i].id, food[i].name, food[i].type,
               food[i].quantity, food[i].days_to_expire, food[i].demand);
    }
}
