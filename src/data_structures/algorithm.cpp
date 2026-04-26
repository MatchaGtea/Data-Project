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
    // TODO (Member 2): BFS for unweighted shortest path (fewest hops)
    // Steps:
    // 1. Init visited[] and parent[] arrays
    // 2. Enqueue startNode
    // 3. While queue not empty:
    //    a. Dequeue node u
    //    b. If u == endNode -> printPath and return
    //    c. For each edge of u -> enqueue unvisited neighbors
    // 4. If queue empty and end not reached -> no path
    std::cout << "TODO: BFS\n";
}
