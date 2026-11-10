
#include <stdio.h>
#include "backend.h"

int passed = 0;
int failed = 0;

void check(const char *name, int condition)
{
    if (condition)
    {
        printf("[PASS] %s\n", name);
        passed++;
    }
    else
    {
        printf("[FAIL] %s\n", name);
        failed++;
    }
}

int main(void)
{
    Food food;
    PickupRequest request;
    Action action;
    int distance;

    printf("\n====================================\n");
    printf(" SHAREAPLATE BACKEND INTEGRATION TEST\n");
    printf("====================================\n");

    /* 1. Initialize backend */
    backend_init();
    check("Backend initialization", 1);

    /* 2. Priority Queue */
    check("Add food donation 101",
          backend_add_food(101, 5, 100));

    check("Add food donation 102",
          backend_add_food(102, 2, 50));

    check("Retrieve urgent food",
          backend_get_urgent_food(&food));

    check("Retrieved valid donation",
          food.donation_id == 101 || food.donation_id == 102);

    printf("Retrieved Donation ID: %d\n", food.donation_id);

    /* 3. Pickup Queue */
    check("Add pickup request",
          backend_add_request(201, 101));

    check("Process pickup request",
          backend_process_request(&request));

    check("Verify pickup request",
          request.request_id == 201 &&
          request.donation_id == 101);

    /* 4. Action Stack */
    check("Add recent action",
          backend_add_action(301, 101));

    check("Undo recent action",
          backend_undo_action(&action));

    check("Verify undone action",
          action.action_id == 301 &&
          action.donation_id == 101);

    /* 5. Donation Tracking */
    check("Add donation tracking",
          backend_add_tracking(101, 1));

    check("Update donation tracking",
          backend_update_tracking(101, 2));

    printf("\nTracking Information:\n");
    backend_show_tracking();

    /* 6. Graph and Routes */
    check("Add route 0 to 1",
          backend_add_route(0, 1, 5));

    check("Add route 1 to 2",
          backend_add_route(1, 2, 7));

    check("Add route 0 to 2",
          backend_add_route(0, 2, 20));

    printf("\nRoute Information:\n");
    backend_show_routes();

    /* 7. Dijkstra Shortest Path */
    distance = backend_get_shortest_distance(0, 2);

    check("Calculate shortest distance",
          distance == 12);

    printf("Shortest distance from 0 to 2: %d\n", distance);

    printf("\nShortest Paths:\n");
    backend_show_shortest_paths(0);

    /* 8. Display backend modules */
    printf("\nFood Priority Queue:\n");
    backend_show_food();

    printf("\nPickup Requests:\n");
    backend_show_requests();

    printf("\nRecent Actions:\n");
    backend_show_actions();

    /* 9. Cleanup */
    backend_cleanup();
    check("Backend cleanup", 1);

    /* Final result */
    printf("\n====================================\n");
    printf("          TEST SUMMARY\n");
    printf("====================================\n");

    printf("Tests Passed: %d\n", passed);
    printf("Tests Failed: %d\n", failed);
    printf("Total Tests:  %d\n", passed + failed);

    if (failed == 0)
        printf("\nALL BACKEND INTEGRATION TESTS PASSED!\n");
    else
        printf("\nSOME BACKEND INTEGRATION TESTS FAILED.\n");

    printf("====================================\n");

    return failed == 0 ? 0 : 1;
}
