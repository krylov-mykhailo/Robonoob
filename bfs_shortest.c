#include "bfs.h"
#include <stdlib.h>

vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len) {
    if (!g || start >= GraphV(g) || end >= GraphV(g)) return NULL;

    PathsPtr p = bfs(g, start);

    if (!p->marked[end]) {
        *path_len = 0;
        PathsDestroy(p);
        return NULL;
    }

    vertex_t *path = malloc(GraphV(g) * sizeof(vertex_t));
    int len = 0;
    for (vertex_t v = end; v != start; v = p->edge_to[v]) {
        path[len++] = v;
    }
    path[len++] = start;

    for (int i = 0; i < len / 2; i++) {
        vertex_t tmp = path[i];
        path[i] = path[len - i - 1];
        path[len - i - 1] = tmp;
    }

    *path_len = len;
    PathsDestroy(p);
    return path;
}