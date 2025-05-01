#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Node {
    Item item;
    struct Node *next;
} Node;

struct Queue {
    Node *first;
    Node *last;
};

QueuePtr QueueInit() {
    QueuePtr q = malloc(sizeof(struct Queue));
    q->first = q->last = NULL;
    return q;
}

int QueueEmpty(QueuePtr q) {
    return q->first == NULL;
}

void enqueue(QueuePtr q, Item item) {
    Node *n = malloc(sizeof(Node));
    n->item = item;
    n->next = NULL;
    if (q->last) q->last->next = n;
    else q->first = n;
    q->last = n;
}

Item dequeue(QueuePtr q) {
    if (QueueEmpty(q)) { assert(0); }
    Node *n = q->first;
    Item item = n->item;
    q->first = n->next;
    if (!q->first) q->last = NULL;
    free(n);
    return item;
}

void QueueDestroy(QueuePtr q) {
    while (!QueueEmpty(q)) dequeue(q);
    free(q);
}