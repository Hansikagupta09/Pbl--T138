#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "models.h"

#define TABLE_SIZE 20

typedef struct {
    int used;
    Donation donation;
} HashEntry;

typedef struct {
    HashEntry table[TABLE_SIZE];
} HashTable;

void initHashTable(HashTable *ht);
void insertDonation(HashTable *ht, Donation d);
Donation *searchDonation(HashTable *ht, int id);
void displayHashTable(HashTable *ht);

#endif
