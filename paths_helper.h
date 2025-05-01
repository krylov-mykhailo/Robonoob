#ifndef PATHS_HELPER_H
#define PATHS_HELPER_H

#include "graph.h"

typedef struct Paths {
    vertex_t *edge_to;
    char *marked;
    int vertices;
} *PathsPtr;

PathsPtr fromGraph(const GraphPtr g, vertex_t s);
void PathsDestroy(PathsPtr p);
void printPath(vertex_t *path, int len);

#endif