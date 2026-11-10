#include <stdio.h>
#include "allocation.h"

void fairAllocation(int foodQuantity, NGO ngos[], int n) {
    int i;
    int totalRequirement = 0;
    int remaining = foodQuantity;

    for (i = 0; i < n; i++)
        totalRequirement += ngos[i].required_quantity;

    printf("\n--- Fair Food Allocation ---\n");

    if (totalRequirement == 0) {
        printf("No NGO requirements available.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        int allocation;

        if (remaining <= 0)
            allocation = 0;
        else if (foodQuantity >= totalRequirement)
            allocation = ngos[i].required_quantity;
        else
            allocation = (foodQuantity * ngos[i].required_quantity)
                         / totalRequirement;

        if (allocation > ngos[i].capacity)
            allocation = ngos[i].capacity;

        printf("%s receives %d units.\n", ngos[i].name, allocation);
        remaining -= allocation;
    }

    printf("Remaining food: %d units.\n", remaining);
}
