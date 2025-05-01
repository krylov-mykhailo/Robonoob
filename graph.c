#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    vertex_t *neighbors;
    int size;
    int capacity;
} Vector;

#define INITIAL_CAPACITY 4

static int add_adjacent_vertex(Vector *list, vertex_t v) {
    if (list->size >= list->capacity) {
        int new_capacity = list->capacity == 0 ? INITIAL_CAPACITY : list->capacity * 2;
        vertex_t *new_data = realloc(list->neighbors, new_capacity * sizeof(vertex_t));
        if (new_data == NULL) return 0;
        list->neighbors = new_data;
        list->capacity = new_capacity;
    }
    list->neighbors[list->size++] = v;
    return 1;
}

struct Graph {
    vertex_t V;
    edge_t E;
    Vector *adj;
};

GraphPtr GraphInit(int num_vertices) {
    GraphPtr g = malloc(sizeof(struct Graph));
    if (!g) return NULL;
    g->V = num_vertices;
    g->E = 0;
    g->adj = calloc(num_vertices, sizeof(Vector));
    if (!g->adj) { free(g); return NULL; }
    return g;
}

void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w) {
    if (v >= g->V || w >= g->V) return;
    add_adjacent_vertex(&g->adj[v], w);
    add_adjacent_vertex(&g->adj[w], v);
    g->E++;
}

const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size) {
    if (v >= g->V || !size) return NULL;
    *size = g->adj[v].size;
    return g->adj[v].neighbors;
}

vertex_t GraphV(const GraphPtr g) { return g->V; }
edge_t GraphE(const GraphPtr g) { return g->E; }

void GraphDestroy(GraphPtr g) {
    if (!g) return;
    for (int i = 0; i < g->V; i++) {
        free(g->adj[i].neighbors);
    }
    free(g->adj);
    free(g);
}