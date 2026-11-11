#include <stdio.h>
#include "waste_detection.h"

int calculateWasteRisk(Food food) {
    int score = 0;

    if (food.days_to_expire <= 1)
        score += 60;
    else if (food.days_to_expire <= 3)
        score += 40;
    else if (food.days_to_expire <= 7)
        score += 20;

    if (food.quantity > food.demand * 2)
        score += 30;
    else if (food.quantity > food.demand)
        score += 15;

    return score;
}

void displayWasteRisk(Food food) {
    int score = calculateWasteRisk(food);

    printf("\nFood: %s | Waste Risk Score: %d | ", food.name, score);

    if (score >= 60)
        printf("HIGH RISK\n");
    else if (score >= 30)
        printf("MEDIUM RISK\n");
    else
        printf("LOW RISK\n");
}
