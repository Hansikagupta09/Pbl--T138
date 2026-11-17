#ifndef REPRIORITIZATION_H
#define REPRIORITIZATION_H

#include "models.h"

int calculatePriority(Food food);
void reprioritizeFood(Food food[], int n);
void displayPriority(Food food[], int n);

#endif
