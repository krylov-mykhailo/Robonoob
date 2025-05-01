#include "paths_helper.h"
#include <stdlib.h>
#include <stdio.h>

PathsPtr fromGraph(const GraphPtr g, vertex_t s) {
    PathsPtr p = malloc(sizeof(struct Paths));
    int V = GraphV(g);
    p->vertices = V;
    p->marked = calloc(V, sizeof(char));
    p->edge_to = malloc(V * sizeof(vertex_t));
    return p;
}

void PathsDestroy(PathsPtr p) {
    if (!p) return;
    free(p->marked);
    free(p->edge_to);
    free(p);
}

void printPath(vertex_t *path, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}