#ifndef STACK_H
#define STACK_H

#define MAX_ACTIONS 100

typedef struct {
    int action_id;
    int donation_id;
} Action;

void stack_init(void);
int stack_push(int action_id, int donation_id);
int stack_pop(Action *result);
void stack_display(void);
int stack_count(void);

#endif