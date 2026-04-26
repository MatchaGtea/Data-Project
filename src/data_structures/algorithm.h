#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "graph.h"

void dijkstra(Graph* g, const char* startName, const char* endName);
void bfs(Graph* g, const char* startName, const char* endName);

#endif
