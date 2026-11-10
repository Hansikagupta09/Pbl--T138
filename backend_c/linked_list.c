#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

static TrackingNode *head = NULL;

/* Convert status number into readable text */
const char *tracking_status_name(int status)
{
    switch (status)
    {
        case 1:
            return "DONATED";

        case 2:
            return "MATCHED";

        case 3:
            return "PICKUP_PENDING";

        case 4:
            return "IN_TRANSIT";

        case 5:
            return "DELIVERED";

        default:
            return "UNKNOWN";
    }
}

/* Initialize linked list */
void tracking_init(void)
{
    tracking_clear();
}

/* Add a new tracking record */
int tracking_add(int donation_id, int status)
{
    TrackingNode *new_node;
    TrackingNode *temp;

    if (donation_id <= 0)
        return 0;

    new_node = (TrackingNode *)malloc(sizeof(TrackingNode));

    if (new_node == NULL)
        return 0;

    new_node->donation_id = donation_id;
    new_node->status = status;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new_node;
    }

    return 1;
}

/* Update donation status */
int tracking_update(int donation_id, int status)
{
    TrackingNode *temp = head;

    while (temp != NULL)
    {
        if (temp->donation_id == donation_id)
        {
            temp->status = status;
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

/* Display all tracking records */
void tracking_display(void)
{
    TrackingNode *temp = head;

    printf("\n--- DONATION TRACKING LINKED LIST ---\n");

    if (head == NULL)
    {
        printf("No tracking records.\n");
        return;
    }

    while (temp != NULL)
    {
        printf("Donation ID: %d | Status: %s\n",
               temp->donation_id,
               tracking_status_name(temp->status));

        temp = temp->next;
    }
}

/* Free all linked-list nodes */
void tracking_clear(void)
{
    TrackingNode *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}