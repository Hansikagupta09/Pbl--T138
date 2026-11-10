#include <stdio.h>
#include "backend.h"
#include "priority_queue.h"
#include "linked_list.h"

/* Clear invalid input */
static void clear_input(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

/* Display main menu */
static void print_menu(void)
{
    printf("\n============================================\n");
    printf("       FOOD RESCUE SYSTEM - BACKEND\n");
    printf("============================================\n");

    printf("1.  Add food donation\n");
    printf("2.  View food priority queue\n");
    printf("3.  Find most urgent food\n");

    printf("4.  Add pickup request\n");
    printf("5.  Process pickup request\n");
    printf("6.  View pickup requests\n");

    printf("7.  Add recent action\n");
    printf("8.  Undo last action\n");
    printf("9.  View recent actions\n");

    printf("10. Add donation tracking\n");
    printf("11. Update donation status\n");
    printf("12. View donation tracking\n");

    printf("13. Add road / route\n");
    printf("14. View road graph\n");
    printf("15. Find shortest routes using Dijkstra\n");
    printf("16. Find distance between two locations\n");

    printf("0.  Exit\n");

    printf("============================================\n");
}

/* Main function */
int main(void)
{
    int choice;

    backend_init();

    while (1)
    {
        print_menu();

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Enter a number.\n");
            clear_input();
            continue;
        }

        if (choice == 0)
            break;

        switch (choice)
        {
            /* ================= FOOD ================= */

            case 1:
            {
                int donation_id;
                int expiry;
                int quantity;

                printf("Donation ID: ");
                scanf("%d", &donation_id);

                printf("Expiry time (hours): ");
                scanf("%d", &expiry);

                printf("Quantity: ");
                scanf("%d", &quantity);

                if (backend_add_food(
                        donation_id,
                        expiry,
                        quantity))
                {
                    printf("Donation added successfully.\n");

                    printf("Priority assigned: %d\n",
                           calculate_priority(expiry));
                }
                else
                {
                    printf("Could not add donation.\n");
                }

                break;
            }

            case 2:
            {
                backend_show_food();
                break;
            }

            case 3:
            {
                Food food;

                if (backend_get_urgent_food(&food))
                {
                    printf("\nMOST URGENT DONATION\n");

                    printf("Donation ID : %d\n",
                           food.donation_id);

                    printf("Expiry      : %d hours\n",
                           food.expiry_hours);

                    printf("Quantity    : %d\n",
                           food.quantity);

                    printf("Priority    : %d\n",
                           food.priority);
                }
                else
                {
                    printf("No food donations available.\n");
                }

                break;
            }

            /* ================= QUEUE ================= */

            case 4:
            {
                int request_id;
                int donation_id;

                printf("Request ID: ");
                scanf("%d", &request_id);

                printf("Donation ID: ");
                scanf("%d", &donation_id);

                if (backend_add_request(
                        request_id,
                        donation_id))
                {
                    printf("Pickup request added.\n");
                }
                else
                {
                    printf("Could not add request.\n");
                }

                break;
            }

            case 5:
            {
                PickupRequest request;

                if (backend_process_request(&request))
                {
                    printf(
                        "Processed Request ID: %d | Donation ID: %d\n",
                        request.request_id,
                        request.donation_id);
                }
                else
                {
                    printf("No pending pickup request.\n");
                }

                break;
            }

            case 6:
            {
                backend_show_requests();
                break;
            }

            /* ================= STACK ================= */

            case 7:
            {
                int action_id;
                int donation_id;

                printf("Action ID: ");
                scanf("%d", &action_id);

                printf("Donation ID: ");
                scanf("%d", &donation_id);

                if (backend_add_action(
                        action_id,
                        donation_id))
                {
                    printf("Action pushed onto stack.\n");
                }
                else
                {
                    printf("Could not add action.\n");
                }

                break;
            }

            case 8:
            {
                Action action;

                if (backend_undo_action(&action))
                {
                    printf("Last action removed.\n");

                    printf("Action ID: %d | Donation ID: %d\n",
                           action.action_id,
                           action.donation_id);
                }
                else
                {
                    printf("No actions to undo.\n");
                }

                break;
            }

            case 9:
            {
                backend_show_actions();
                break;
            }

            /* ================= TRACKING ================= */

            case 10:
            {
                int donation_id;
                int status;

                printf("Donation ID: ");
                scanf("%d", &donation_id);

                printf("\n1. DONATED");
                printf("\n2. MATCHED");
                printf("\n3. PICKUP_PENDING");
                printf("\n4. IN_TRANSIT");
                printf("\n5. DELIVERED\n");

                printf("Enter status: ");
                scanf("%d", &status);

                if (backend_add_tracking(
                        donation_id,
                        status))
                {
                    printf("Tracking record added.\n");
                }
                else
                {
                    printf("Could not add tracking record.\n");
                }

                break;
            }

            case 11:
            {
                int donation_id;
                int status;

                printf("Donation ID: ");
                scanf("%d", &donation_id);

                printf("New status (1-5): ");
                scanf("%d", &status);

                if (backend_update_tracking(
                        donation_id,
                        status))
                {
                    printf("Donation status updated.\n");
                }
                else
                {
                    printf("Donation ID not found.\n");
                }

                break;
            }

            case 12:
            {
                backend_show_tracking();
                break;
            }

            /* ================= GRAPH ================= */

            case 13:
            {
                int source;
                int destination;
                int distance;

                printf("Source location (0-9): ");
                scanf("%d", &source);

                printf("Destination location (0-9): ");
                scanf("%d", &destination);

                printf("Distance (km): ");
                scanf("%d", &distance);

                if (backend_add_route(
                        source,
                        destination,
                        distance))
                {
                    printf("Route added successfully.\n");
                }
                else
                {
                    printf("Could not add route.\n");
                }

                break;
            }

            case 14:
            {
                backend_show_routes();
                break;
            }

            case 15:
            {
                int source;

                printf("Source location (0-9): ");
                scanf("%d", &source);

                backend_show_shortest_paths(source);

                break;
            }

            case 16:
            {
                int source;
                int destination;
                int distance;

                printf("Source location (0-9): ");
                scanf("%d", &source);

                printf("Destination location (0-9): ");
                scanf("%d", &destination);

                distance =
                    backend_get_shortest_distance(
                        source,
                        destination);

                if (distance == -1)
                {
                    printf("Destination is not reachable.\n");
                }
                else
                {
                    printf("Shortest distance: %d km\n",
                           distance);
                }

                break;
            }

            default:
            {
                printf("Invalid choice. Try again.\n");
            }
        }
    }

    backend_cleanup();

    printf("\nFood Rescue Backend closed successfully.\n");

    return 0;
}