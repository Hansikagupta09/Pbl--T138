#include <string.h>
#include "matching.h"

int findBestNGO(Food food, NGO ngos[], int n) {
    int i;
    int bestIndex = -1;
    int bestScore = -1;

    for (i = 0; i < n; i++) {
        int score = 0;

        if (strcmp(food.type, ngos[i].required_type) == 0)
            score += 50;

        if (ngos[i].required_quantity > 0 &&
            food.quantity >= ngos[i].required_quantity)
            score += 30;

        if (ngos[i].capacity >= food.quantity)
            score += 20;

        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }

    return bestIndex;
}
