#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MAX_FOOD 100

typedef struct {
    int donation_id;
    int expiry_hours;
    int quantity;
    int priority;
} Food;

void pq_init(void);
int calculate_priority(int expiry_hours);
int pq_insert(int donation_id, int expiry_hours, int quantity);
int pq_get_urgent(Food *result);
void pq_display(void);
int pq_count(void);

#endif