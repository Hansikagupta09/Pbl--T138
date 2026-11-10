
#include <stdio.h>
#include <assert.h>
#include "graph.h"

int main(void)
{
    printf("\n===== GRAPH TESTING =====\n");

    /* TEST 1: Initialization */
    graph_init();
    assert(graph_get_distance(0, 1) == 0);
    printf("TEST 1 PASSED: Graph initialization\n");

    /* TEST 2: Add an edge */
    assert(graph_add_edge(0, 1, 10) == 1);
    printf("TEST 2 PASSED: Edge insertion\n");

    /* TEST 3: Undirected connection */
    assert(graph_get_distance(0, 1) == 10);
    assert(graph_get_distance(1, 0) == 10);
    printf("TEST 3 PASSED: Undirected connection\n");

    /* TEST 4: Add multiple edges */
    assert(graph_add_edge(1, 2, 20) == 1);
    assert(graph_add_edge(2, 3, 15) == 1);
    assert(graph_add_edge(0, 3, 40) == 1);
    printf("TEST 4 PASSED: Multiple edge insertion\n");

    /* TEST 5: Check distances */
    assert(graph_get_distance(1, 2) == 20);
    assert(graph_get_distance(2, 3) == 15);
    assert(graph_get_distance(0, 3) == 40);
    printf("TEST 5 PASSED: Distance retrieval\n");

    /* TEST 6: Invalid negative source */
    assert(graph_add_edge(-1, 2, 10) == 0);
    printf("TEST 6 PASSED: Negative location handling\n");

    /* TEST 7: Invalid vertex */
    assert(graph_add_edge(0, MAX_VERTICES, 10) == 0);
    printf("TEST 7 PASSED: Out-of-range location handling\n");

    /* TEST 8: Same source and destination */
    assert(graph_add_edge(2, 2, 10) == 0);
    printf("TEST 8 PASSED: Self-loop prevention\n");

    /* TEST 9: Invalid distance */
    assert(graph_add_edge(1, 3, 0) == 0);
    assert(graph_add_edge(1, 3, -5) == 0);
    printf("TEST 9 PASSED: Invalid distance handling\n");

    /* TEST 10: Invalid distance lookup */
    assert(graph_get_distance(-1, 2) == 0);
    assert(graph_get_distance(0, MAX_VERTICES) == 0);
    printf("TEST 10 PASSED: Invalid lookup handling\n");

    /* TEST 11: Display graph */
    printf("\nDisplaying graph:\n");
    graph_display();
    printf("TEST 11 PASSED: Graph display\n");

    /* TEST 12: Reinitialize graph */
    graph_init();
    assert(graph_get_distance(0, 1) == 0);
    assert(graph_get_distance(1, 2) == 0);
    printf("TEST 12 PASSED: Graph reinitialization\n");

    printf("\n===== ALL GRAPH TESTS PASSED =====\n");

    return 0;
}
