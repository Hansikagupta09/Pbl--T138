#include <stdio.h>
#include "stack.h"

static Action actions[MAX_ACTIONS];
static int top = -1;

/* Initialize stack */
void stack_init(void)
{
    top = -1;
}

/* Add action to stack */
int stack_push(int action_id, int donation_id)
{
    if (top >= MAX_ACTIONS - 1 ||
        action_id <= 0 ||
        donation_id <= 0)
    {
        return 0;
    }

    top++;

    actions[top].action_id = action_id;
    actions[top].donation_id = donation_id;

    return 1;
}

/* Remove the most recent action */
int stack_pop(Action *result)
{
    if (top < 0 || result == NULL)
        return 0;

    *result = actions[top];

    top--;

    return 1;
}

/* Display recent actions */
void stack_display(void)
{
    int i;

    printf("\n--- RECENT ACTION STACK ---\n");

    if (top < 0)
    {
        printf("No actions available.\n");
        return;
    }

    for (i = top; i >= 0; i--)
    {
        printf("Action ID: %d | Donation ID: %d\n",
               actions[i].action_id,
               actions[i].donation_id);
    }
}

/* Return number of actions */
int stack_count(void)
{
    return top + 1;
}