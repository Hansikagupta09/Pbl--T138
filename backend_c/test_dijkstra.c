
#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "dijkstra.h"

int main(void)
{
    printf("\n===== DIJKSTRA TESTING =====\n");

    /* TEST 1: Initialize graph */
    graph_init();
    assert(dijkstra_distance(0, 1) == -1);
    printf("TEST 1 PASSED: Empty graph handling\n");

    /* TEST 2: Create weighted graph */
    graph_add_edge(0, 1, 10);
    graph_add_edge(1, 2, 20);
    graph_add_edge(0, 2, 50);
    graph_add_edge(2, 3, 15);
    graph_add_edge(1, 3, 40);
    printf("TEST 2 PASSED: Graph creation\n");

    /* TEST 3: Direct shortest distance */
    assert(dijkstra_distance(0, 1) == 10);
    printf("TEST 3 PASSED: Direct path calculation\n");

    /* TEST 4: Shortest path through intermediate node */
    assert(dijkstra_distance(0, 2) == 30);
    printf("TEST 4 PASSED: Intermediate path calculation\n");

    /* TEST 5: Multiple route comparison */
    assert(dijkstra_distance(0, 3) == 45);
    printf("TEST 5 PASSED: Shortest route selection\n");

    /* TEST 6: Same source and destination */
    assert(dijkstra_distance(2, 2) == 0);
    printf("TEST 6 PASSED: Same location handling\n");

    /* TEST 7: Reverse route */
    assert(dijkstra_distance(3, 0) == 45);
    printf("TEST 7 PASSED: Reverse path calculation\n");

    /* TEST 8: Unreachable location */
    graph_init();
    graph_add_edge(0, 1, 10);
    assert(dijkstra_distance(0, 5) == -1);
    printf("TEST 8 PASSED: Unreachable location handling\n");

    /* TEST 9: Invalid source */
    assert(dijkstra_distance(-1, 2) == -1);
    printf("TEST 9 PASSED: Invalid source handling\n");

    /* TEST 10: Invalid destination */
    assert(dijkstra_distance(0, MAX_VERTICES) == -1);
    printf("TEST 10 PASSED: Invalid destination handling\n");

    /* TEST 11: Display shortest paths */
    printf("\nShortest paths from location 0:\n");
    dijkstra_shortest_paths(0);
    printf("TEST 11 PASSED: Shortest path display\n");

    /* TEST 12: Invalid source for display */
    printf("\nInvalid source test:\n");
    dijkstra_shortest_paths(-1);
    printf("TEST 12 PASSED: Invalid source display handling\n");

    printf("\n===== ALL DIJKSTRA TESTS PASSED =====\n");

    return 0;
}
