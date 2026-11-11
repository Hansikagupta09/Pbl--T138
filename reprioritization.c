#include <stdio.h>
#include "reprioritization.h"

static void swapFood(Food *a, Food *b) {
    Food temp = *a;
    *a = *b;
    *b = temp;
}

int calculatePriority(Food food) {
    int score = 0;

    if (food.days_to_expire <= 1)
        score += 60;
    else if (food.days_to_expire <= 3)
        score += 40;
    else if (food.days_to_expire <= 7)
        score += 20;

    score += food.demand;

    if (food.quantity > food.demand)
        score += 10;

    return score;
}

void reprioritizeFood(Food food[], int n) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (calculatePriority(food[j]) < calculatePriority(food[j + 1]))
                swapFood(&food[j], &food[j + 1]);
        }
    }
}

void displayPriority(Food food[], int n) {
    int i;

    printf("\n--- Food Priority ---\n");

    for (i = 0; i < n; i++) {
        printf("%s -> Priority Score: %d\n",
               food[i].name, calculatePriority(food[i]));
    }
}
