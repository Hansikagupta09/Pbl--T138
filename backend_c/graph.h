#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 10
#define INF 1000000

void graph_init(void);
int graph_add_edge(int source, int destination, int distance);
void graph_display(void);
int graph_get_distance(int source, int destination);

#endif