#ifndef QUEUE_H
#define QUEUE_H

#define INF 999999

// --- Regular Queue (used by BFS) ---

struct QNode {
    int data;
    QNode* next;
};

struct Queue {
    QNode* front;
    QNode* rear;
};

Queue* createQueue();
void enqueue(Queue* q, int data);
int dequeue(Queue* q);
bool isQueueEmpty(Queue* q);
void freeQueue(Queue* q);

// --- Priority Queue (used by Dijkstra) ---
// Linked list sorted by distance ascending

struct PQNode {
    int nodeId;
    int distance;
    PQNode* next;
};

struct PriorityQueue {
    PQNode* head;
};

PriorityQueue* createPQ();
void pqInsert(PriorityQueue* pq, int nodeId, int distance);
PQNode pqExtractMin(PriorityQueue* pq);
bool isPQEmpty(PriorityQueue* pq);
void freePQ(PriorityQueue* pq);

#endif
