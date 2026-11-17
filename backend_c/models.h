#ifndef MODELS_H
#define MODELS_H

#define MAX_NAME 50
#define MAX_TYPE 30

typedef struct {
    int id;
    char name[MAX_NAME];
    char type[MAX_TYPE];
    int quantity;
    int days_to_expire;
    int demand;
} Food;

typedef struct {
    int id;
    char name[MAX_NAME];
    char required_type[MAX_TYPE];
    int required_quantity;
    int capacity;
} NGO;

typedef struct {
    int id;
    int donor_id;
    int food_id;
    int quantity;
} Donation;

#endif
