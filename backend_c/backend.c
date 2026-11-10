#include "backend.h"
#include "linked_list.h"
#include "graph.h"
#include "dijkstra.h"

/* Initialize the complete backend */
void backend_init(void)
{
    pq_init();
    queue_init();
    stack_init();
    tracking_init();
    graph_init();
}

/* ================= FOOD PRIORITY ================= */

int backend_add_food(int donation_id, int expiry_hours, int quantity)
{
    return pq_insert(donation_id, expiry_hours, quantity);
}

int backend_get_urgent_food(Food *result)
{
    return pq_get_urgent(result);
}

void backend_show_food(void)
{
    pq_display();
}

/* ================= PICKUP REQUESTS ================= */

int backend_add_request(int request_id, int donation_id)
{
    return queue_enqueue(request_id, donation_id);
}

int backend_process_request(PickupRequest *result)
{
    return queue_dequeue(result);
}

void backend_show_requests(void)
{
    queue_display();
}

/* ================= RECENT ACTIONS ================= */

int backend_add_action(int action_id, int donation_id)
{
    return stack_push(action_id, donation_id);
}

int backend_undo_action(Action *result)
{
    return stack_pop(result);
}

void backend_show_actions(void)
{
    stack_display();
}

/* ================= DONATION TRACKING ================= */

int backend_add_tracking(int donation_id, int status)
{
    return tracking_add(donation_id, status);
}

int backend_update_tracking(int donation_id, int status)
{
    return tracking_update(donation_id, status);
}

void backend_show_tracking(void)
{
    tracking_display();
}

/* ================= ROUTES ================= */

int backend_add_route(int source, int destination, int distance)
{
    return graph_add_edge(source, destination, distance);
}

void backend_show_routes(void)
{
    graph_display();
}

void backend_show_shortest_paths(int source)
{
    dijkstra_shortest_paths(source);
}

int backend_get_shortest_distance(int source, int destination)
{
    return dijkstra_distance(source, destination);
}

/* ================= CLEANUP ================= */

void backend_cleanup(void)
{
    tracking_clear();
}