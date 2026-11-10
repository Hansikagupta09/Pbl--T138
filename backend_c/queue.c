#include <stdio.h>
#include "queue.h"

static PickupRequest requests[MAX_REQUESTS];

static int front = 0;
static int rear = 0;
static int count = 0;

/* Initialize queue */
void queue_init(void)
{
    front = 0;
    rear = 0;
    count = 0;
}

/* Add a pickup request */
int queue_enqueue(int request_id, int donation_id)
{
    if (count >= MAX_REQUESTS ||
        request_id <= 0 ||
        donation_id <= 0)
    {
        return 0;
    }

    requests[rear].request_id = request_id;
    requests[rear].donation_id = donation_id;

    rear = (rear + 1) % MAX_REQUESTS;
    count++;

    return 1;
}

/* Remove the first pickup request */
int queue_dequeue(PickupRequest *result)
{
    if (count == 0 || result == NULL)
        return 0;

    *result = requests[front];

    front = (front + 1) % MAX_REQUESTS;
    count--;

    return 1;
}

/* Display all pending requests */
void queue_display(void)
{
    int i;
    int index;

    printf("\n--- PICKUP / DELIVERY QUEUE ---\n");

    if (count == 0)
    {
        printf("No pending requests.\n");
        return;
    }

    index = front;

    for (i = 0; i < count; i++)
    {
        printf("Request ID: %d | Donation ID: %d\n",
               requests[index].request_id,
               requests[index].donation_id);

        index = (index + 1) % MAX_REQUESTS;
    }
}

/* Return number of pending requests */
int queue_count(void)
{
    return count;
}