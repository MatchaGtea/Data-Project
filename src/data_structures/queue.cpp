#include <iostream>
#include "queue.h"

// --- Regular Queue ---

Queue* createQueue() {
    Queue* q = new Queue;
    q->front = q->rear = nullptr;
    return q;
}

void enqueue(Queue* q, int data) {
    QNode* node = new QNode;
    node->data = data;
    node->next = nullptr;
    if (!q->rear) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) return -1;
    QNode* tmp = q->front;
    int val = tmp->data;
    q->front = q->front->next;
    if (!q->front) q->rear = nullptr;
    delete tmp;
    return val;
}

bool isQueueEmpty(Queue* q) {
    return q->front == nullptr;
}

void freeQueue(Queue* q) {
    while (!isQueueEmpty(q)) dequeue(q);
    delete q;
}

// --- Priority Queue (Min) ---

PriorityQueue* createPQ() {
    PriorityQueue* pq = new PriorityQueue;
    pq->head = nullptr;
    return pq;
}

void pqInsert(PriorityQueue* pq, int nodeId, int distance) {
    PQNode* node = new PQNode;
    node->nodeId = nodeId;
    node->distance = distance;
    node->next = nullptr;

    // Insert in sorted order (ascending by distance)
    if (!pq->head || distance < pq->head->distance) {
        node->next = pq->head;
        pq->head = node;
        return;
    }
    PQNode* curr = pq->head;
    while (curr->next && curr->next->distance <= distance)
        curr = curr->next;
    node->next = curr->next;
    curr->next = node;
}

PQNode pqExtractMin(PriorityQueue* pq) {
    PQNode result = {-1, INF, nullptr};
    if (!pq->head) return result;
    PQNode* tmp = pq->head;
    result.nodeId = tmp->nodeId;
    result.distance = tmp->distance;
    pq->head = tmp->next;
    delete tmp;
    return result;
}

bool isPQEmpty(PriorityQueue* pq) {
    return pq->head == nullptr;
}

void freePQ(PriorityQueue* pq) {
    while (!isPQEmpty(pq)) pqExtractMin(pq);
    delete pq;
}
