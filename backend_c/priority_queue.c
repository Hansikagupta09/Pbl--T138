#include <stdio.h>
#include "priority_queue.h"

static Food heap[MAX_FOOD];
static int heap_size = 0;

/* Swap two food records */
static void swap_food(Food *a, Food *b)
{
    Food temp = *a;
    *a = *b;
    *b = temp;
}

/* Check which food has higher priority */
static int is_higher_priority(Food a, Food b)
{
    if (a.priority != b.priority)
        return a.priority < b.priority;

    if (a.expiry_hours != b.expiry_hours)
        return a.expiry_hours < b.expiry_hours;

    return a.donation_id < b.donation_id;
}

/* Initialize priority queue */
void pq_init(void)
{
    heap_size = 0;
}

/* Calculate priority based on expiry */
int calculate_priority(int expiry_hours)
{
    if (expiry_hours <= 2)
        return 1;

    if (expiry_hours <= 5)
        return 2;

    if (expiry_hours <= 10)
        return 3;

    return 4;
}

/* Insert food donation */
int pq_insert(int donation_id, int expiry_hours, int quantity)
{
    int i;

    if (heap_size >= MAX_FOOD ||
        donation_id <= 0 ||
        expiry_hours < 0 ||
        quantity <= 0)
    {
        return 0;
    }

    heap[heap_size].donation_id = donation_id;
    heap[heap_size].expiry_hours = expiry_hours;
    heap[heap_size].quantity = quantity;
    heap[heap_size].priority = calculate_priority(expiry_hours);

    i = heap_size;
    heap_size++;

    /* Move the new element upward */
    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (!is_higher_priority(heap[i], heap[parent]))
            break;

        swap_food(&heap[i], &heap[parent]);
        i = parent;
    }

    return 1;
}

/* Get the most urgent food */
int pq_get_urgent(Food *result)
{
    if (heap_size == 0 || result == NULL)
        return 0;

    *result = heap[0];

    return 1;
}

/* Display priority queue */
void pq_display(void)
{
    int i;

    printf("\n--- FOOD PRIORITY QUEUE / MIN HEAP ---\n");

    if (heap_size == 0)
    {
        printf("No food donations in the queue.\n");
        return;
    }

    for (i = 0; i < heap_size; i++)
    {
        printf("Donation ID: %d | Expiry: %d hrs | Quantity: %d | Priority: %d\n",
               heap[i].donation_id,
               heap[i].expiry_hours,
               heap[i].quantity,
               heap[i].priority);
    }
}

/* Return number of food donations */
int pq_count(void)
{
    return heap_size;
}