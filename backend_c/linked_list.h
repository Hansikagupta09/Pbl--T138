#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct TrackingNode {
    int donation_id;
    int status;
    struct TrackingNode *next;
} TrackingNode;

void tracking_init(void);
int tracking_add(int donation_id, int status);
int tracking_update(int donation_id, int status);
void tracking_display(void);
void tracking_clear(void);

const char *tracking_status_name(int status);

#endif