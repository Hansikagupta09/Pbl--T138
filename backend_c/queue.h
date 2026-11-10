#ifndef QUEUE_H
#define QUEUE_H

#define MAX_REQUESTS 100

typedef struct {
    int request_id;
    int donation_id;
} PickupRequest;

void queue_init(void);
int queue_enqueue(int request_id, int donation_id);
int queue_dequeue(PickupRequest *result);
void queue_display(void);
int queue_count(void);

#endif