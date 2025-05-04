#include "bfs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *data, front, rear;
} Queue;

static Queue* createQueue(int size) {
    Queue* q = malloc(sizeof(Queue));
    q->data = malloc(size * sizeof(int));
    q->front = q->rear = 0;
    return q;
}

static void enqueue(Queue* q, int val) { q->data[q->rear++] = val; }
static int dequeue(Queue* q) { return q->data[q->front++]; }
static bool isEmpty(Queue* q) { return q->front == q->rear; }
static void freeQueue(Queue* q) { free(q->data); free(q); }

void BFS(Graph* g, int start, int dest, int *path, int *length) {
    bool* visited = calloc(g->numVertices, sizeof(bool));
    int* parent = malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; ++i) parent[i] = -1;

    Queue* q = createQueue(g->numVertices);
    enqueue(q, start);
    visited[start] = true;

    bool found = false;

    while (!isEmpty(q)) {
        int curr = dequeue(q);
        if (curr == dest) {
            found = true;
            break;
        }
        for (int i = 0; i < g->numVertices; ++i)
            if (g->adjMatrix[curr][i] && !visited[i]) {
                visited[i] = true;
                parent[i] = curr;
                enqueue(q, i);
            }
    }

    if (found) {
        int len = 0, curr = dest;
        while (curr != -1) {
            path[len++] = curr;
            curr = parent[curr];
        }

        printf("BFS Path: ");
        for (int i = len - 1; i >= 0; --i)
            printf("(%d,%d) ", g->vertices[path[i]].x, g->vertices[path[i]].y);
        printf("\nLength: %d\n", len);

        *length = len;
    } else {
        printf("No path found by BFS\n");
        *length = 0;
    }

    free(visited);
    free(parent);
    freeQueue(q);
}