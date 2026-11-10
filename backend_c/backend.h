#ifndef BACKEND_H
#define BACKEND_H

#include "priority_queue.h"
#include "queue.h"
#include "stack.h"

void backend_init(void);

/* Food Priority */
int backend_add_food(int donation_id, int expiry_hours, int quantity);
int backend_get_urgent_food(Food *result);
void backend_show_food(void);

/* Pickup Requests */
int backend_add_request(int request_id, int donation_id);
int backend_process_request(PickupRequest *result);
void backend_show_requests(void);

/* Recent Actions */
int backend_add_action(int action_id, int donation_id);
int backend_undo_action(Action *result);
void backend_show_actions(void);

/* Donation Tracking */
int backend_add_tracking(int donation_id, int status);
int backend_update_tracking(int donation_id, int status);
void backend_show_tracking(void);

/* Routes */
int backend_add_route(int source, int destination, int distance);
void backend_show_routes(void);
void backend_show_shortest_paths(int source);
int backend_get_shortest_distance(int source, int destination);

/* Cleanup */
void backend_cleanup(void);

#endif