#include "searching.h"

int linearSearchFood(Food food[], int n, int id) {
    int i;
    for (i = 0; i < n; i++) {
        if (food[i].id == id)
            return i;
    }
    return -1;
}

int linearSearchNGO(NGO ngos[], int n, int id) {
    int i;
    for (i = 0; i < n; i++) {
        if (ngos[i].id == id)
            return i;
    }
    return -1;
}

int binarySearchFood(Food food[], int n, int id) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (food[mid].id == id)
            return mid;
        else if (food[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}
