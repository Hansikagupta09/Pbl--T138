#include <stdio.h>
#include "hash_table.h"

static int hashFunction(int id) {
    return id % TABLE_SIZE;
}

void initHashTable(HashTable *ht) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
        ht->table[i].used = 0;
}

void insertDonation(HashTable *ht, Donation d) {
    int index = hashFunction(d.id);
    int start = index;

    while (ht->table[index].used) {
        index = (index + 1) % TABLE_SIZE;
        if (index == start) {
            printf("Hash table is full.\n");
            return;
        }
    }

    ht->table[index].used = 1;
    ht->table[index].donation = d;
}

Donation *searchDonation(HashTable *ht, int id) {
    int index = hashFunction(id);
    int start = index;

    while (ht->table[index].used) {
        if (ht->table[index].donation.id == id)
            return &ht->table[index].donation;

        index = (index + 1) % TABLE_SIZE;
        if (index == start)
            break;
    }

    return NULL;
}

void displayHashTable(HashTable *ht) {
    int i;
    printf("\n--- Hash Table ---\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i].used) {
            printf("[%d] Donation ID: %d, Quantity: %d\n",
                   i,
                   ht->table[i].donation.id,
                   ht->table[i].donation.quantity);
        }
    }
}
