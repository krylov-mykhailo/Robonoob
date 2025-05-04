#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool DFSUtil(Graph* g, int current, int dest, bool *visited, int *path, int *length) {
    visited[current] = true;
    path[(*length)++] = current;

    if (current == dest) return true;

    for (int i = 0; i < g->numVertices; ++i)
        if (g->adjMatrix[current][i] && !visited[i])
            if (DFSUtil(g, i, dest, visited, path, length)) return true;

    (*length)--;
    visited[current] = false;
    return false;
}

void DFS(Graph* g, int start, int dest, int *path, int *length) {
    bool* visited = calloc(g->numVertices, sizeof(bool));

    if (DFSUtil(g, start, dest, visited, path, length)) {
        printf("DFS Path: ");
        for (int i = 0; i < *length; ++i)
            printf("(%d,%d) ", g->vertices[path[i]].x, g->vertices[path[i]].y);
        printf("\nLength: %d\n", *length);
    } else {
        printf("No path found by DFS\n");
    }

    free(visited);
}