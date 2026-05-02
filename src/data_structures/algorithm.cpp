#include <iostream>
#include <cstring>
#include "algorithm.h"
#include "queue.h"

// Helper: get node by id
static Node* getNodeById(Graph* g, int id) {
    Node* curr = g->head;
    while (curr) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return nullptr;
}

// Helper: print path by tracing parent array
static void printPath(Graph* g, int* parent, int startId, int endId) {
    if (endId == startId) {
        Node* n = getNodeById(g, startId);
        if (n) std::cout << n->name;
        return;
    }
    if (parent[endId] == -1) {
        std::cout << "(no path)";
        return;
    }
    printPath(g, parent, startId, parent[endId]);
    Node* n = getNodeById(g, endId);
    if (n) std::cout << " -> " << n->name;
}

void dijkstra(Graph* g, const char* startName, const char* endName) {
    Node* startNode = findNode(g, startName);
    Node* endNode   = findNode(g, endName);
    if (!startNode || !endNode) {
        std::cout << "Location not found.\n";
        return;
    }

    int n = g->nodeCount;
    int* dist   = new int[n];
    int* parent = new int[n];
    bool* visited = new bool[n];

    for (int i = 0; i < n; i++) {
        dist[i]    = INF;
        parent[i]  = -1;
        visited[i] = false;
    }
    dist[startNode->id] = 0;

    PriorityQueue* pq = createPQ();
    pqInsert(pq, startNode->id, 0);

    while (!isPQEmpty(pq)) {
        PQNode curr = pqExtractMin(pq);
        int u = curr.nodeId;
        if (visited[u]) continue;
        visited[u] = true;

        Node* uNode = getNodeById(g, u);
        if (!uNode) continue;

        Edge* e = uNode->edges;
        while (e) {
            int v = e->dest;
            int w = e->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v]   = dist[u] + w;
                parent[v] = u;
                pqInsert(pq, v, dist[v]);
            }
            e = e->next;
        }
    }

    std::cout << "\n=== Shortest Path (Dijkstra) ===\n";
    std::cout << "From: " << startName << "  To: " << endName << "\n";
    if (dist[endNode->id] == INF) {
        std::cout << "No path found.\n";
    } else {
        std::cout << "Path: ";
        printPath(g, parent, startNode->id, endNode->id);
        std::cout << "\nDistance: " << dist[endNode->id] << "\n";
    }

    freePQ(pq);
    delete[] dist;
    delete[] parent;
    delete[] visited;
}

void bfs(Graph* g, const char* startName, const char* endName) {
    Node* startNode = findNode(g, startName);
    Node* endNode = findNode(g, endName);
    if (!startNode || !endNode) {
        std::cout << "Location not found.\n";
        return;
    }

    int n = g->nodeCount;
    bool* visited = new bool[n];
    int* parent = new int[n];
    int* hops = new int[n];

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        parent[i] = -1;
        hops[i] = INF;
    }

    Queue* q = createQueue();
    visited[startNode->id] = true;
    hops[startNode->id] = 0;
    enqueue(q, startNode->id);

    while (!isQueueEmpty(q)) {
        int u = dequeue(q);
        if (u == endNode->id) break;

        Node* uNode = getNodeById(g, u);
        if (!uNode) continue;

        Edge* e = uNode->edges;
        while (e) {
            int v = e->dest;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                hops[v] = hops[u] + 1;
                enqueue(q, v);
            }
            e = e->next;
        }
    }

    std::cout << "\n=== Shortest Path (BFS) ===\n";
    std::cout << "From: " << startName << "  To: " << endName << "\n";
    if (!visited[endNode->id]) {
        std::cout << "No path found.\n";
    } else {
        std::cout << "Path: ";
        printPath(g, parent, startNode->id, endNode->id);
        std::cout << "\nHops: " << hops[endNode->id] << "\n";
    }

    freeQueue(q);
    delete[] visited;
    delete[] parent;
    delete[] hops;
}
