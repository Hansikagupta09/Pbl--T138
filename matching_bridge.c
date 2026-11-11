#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "models.h"
#include "matching.h"

void normalize(char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        s[i] = (char)tolower((unsigned char)s[i]);
}

int main(int argc, char *argv[])
{
    Food food = {0};
    NGO ngo = {0};

    if (argc != 6)
        return 1;

    strncpy(food.type, argv[1], MAX_TYPE - 1);
    food.quantity = atoi(argv[2]);

    strncpy(ngo.name, argv[3], MAX_NAME - 1);
    strncpy(ngo.required_type, argv[4], MAX_TYPE - 1);
    ngo.capacity = atoi(argv[5]);

    normalize(food.type);
    normalize(ngo.required_type);

    int result = findBestNGO(food, &ngo, 1);

    if (result == 0 &&
        strcmp(food.type, ngo.required_type) == 0 &&
        food.quantity > 0 &&
        ngo.capacity >= food.quantity)
    {
        printf("MATCH");
        return 0;
    }

    printf("NO_MATCH");
    return 2;
}
