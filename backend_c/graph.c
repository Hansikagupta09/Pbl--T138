#include <stdio.h>
#include "graph.h"

static int graph[MAX_VERTICES][MAX_VERTICES];

/* Initialize graph */
void graph_init(void)
{
    int i, j;

    for (i = 0; i < MAX_VERTICES; i++)
    {
        for (j = 0; j < MAX_VERTICES; j++)
        {
            graph[i][j] = 0;
        }
    }
}

/* Add a road between two locations */
int graph_add_edge(int source, int destination, int distance)
{
    if (source < 0 || source >= MAX_VERTICES ||
        destination < 0 || destination >= MAX_VERTICES ||
        source == destination ||
        distance <= 0)
    {
        return 0;
    }

    graph[source][destination] = distance;
    graph[destination][source] = distance;

    return 1;
}

/* Display all roads */
void graph_display(void)
{
    int i, j;
    int found = 0;

    printf("\n--- ROAD / LOCATION GRAPH ---\n");

    for (i = 0; i < MAX_VERTICES; i++)
    {
        for (j = i + 1; j < MAX_VERTICES; j++)
        {
            if (graph[i][j] > 0)
            {
                printf("Location %d <-> Location %d = %d km\n",
                       i, j, graph[i][j]);

                found = 1;
            }
        }
    }

    if (!found)
    {
        printf("No routes available.\n");
    }
}

/* Get distance between two directly connected locations */
int graph_get_distance(int source, int destination)
{
    if (source < 0 || source >= MAX_VERTICES ||
        destination < 0 || destination >= MAX_VERTICES)
    {
        return 0;
    }

    return graph[source][destination];
}