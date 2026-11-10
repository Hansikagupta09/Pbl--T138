#include <stdio.h>
#include "dijkstra.h"
#include "graph.h"

/* Find the unvisited location with minimum distance */
static int choose_min_vertex(int distance[], int visited[])
{
    int i;
    int min = INF;
    int vertex = -1;

    for (i = 0; i < MAX_VERTICES; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            vertex = i;
        }
    }

    return vertex;
}

/* Find shortest paths from source to all locations */
void dijkstra_shortest_paths(int source)
{
    int distance[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};

    int i, j, current;

    if (source < 0 || source >= MAX_VERTICES)
    {
        printf("Invalid source location.\n");
        return;
    }

    /* Initially all distances are infinity */
    for (i = 0; i < MAX_VERTICES; i++)
    {
        distance[i] = INF;
    }

    /* Distance from source to itself is 0 */
    distance[source] = 0;

    /* Dijkstra's main loop */
    for (i = 0; i < MAX_VERTICES - 1; i++)
    {
        current = choose_min_vertex(distance, visited);

        if (current == -1)
            break;

        visited[current] = 1;

        /* Check neighboring locations */
        for (j = 0; j < MAX_VERTICES; j++)
        {
            int weight = graph_get_distance(current, j);

            if (weight > 0 &&
                !visited[j] &&
                distance[current] != INF &&
                distance[current] + weight < distance[j])
            {
                distance[j] =
                    distance[current] + weight;
            }
        }
    }

    printf("\n--- SHORTEST DISTANCES FROM LOCATION %d ---\n",
           source);

    for (i = 0; i < MAX_VERTICES; i++)
    {
        if (distance[i] == INF)
        {
            printf("Location %d : Not reachable\n", i);
        }
        else
        {
            printf("Location %d : %d km\n",
                   i, distance[i]);
        }
    }
}

/* Find shortest distance between two locations */
int dijkstra_distance(int source, int destination)
{
    int distance[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};

    int i, j, current;

    if (source < 0 || source >= MAX_VERTICES ||
        destination < 0 || destination >= MAX_VERTICES)
    {
        return -1;
    }

    for (i = 0; i < MAX_VERTICES; i++)
    {
        distance[i] = INF;
    }

    distance[source] = 0;

    for (i = 0; i < MAX_VERTICES - 1; i++)
    {
        current = choose_min_vertex(distance, visited);

        if (current == -1)
            break;

        visited[current] = 1;

        for (j = 0; j < MAX_VERTICES; j++)
        {
            int weight = graph_get_distance(current, j);

            if (weight > 0 &&
                !visited[j] &&
                distance[current] != INF &&
                distance[current] + weight < distance[j])
            {
                distance[j] =
                    distance[current] + weight;
            }
        }
    }

    if (distance[destination] == INF)
        return -1;

    return distance[destination];
}