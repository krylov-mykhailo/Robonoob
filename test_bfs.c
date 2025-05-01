#include "bfs.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_shortest_path() {
    GraphPtr g = GraphInit(6);
    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 1, 3);
    GraphAddEdge(g, 2, 3);
    GraphAddEdge(g, 3, 4);
    GraphAddEdge(g, 4, 5);

    int path_len;
    vertex_t *path = GraphShortestBFS(g, 0, 5, &path_len);

    assert(path != NULL);
    assert(path_len == 5);
    assert(path[0] == 0);
    assert(path[path_len - 1] == 5);

    printf("Shortest path from 0 to 5 (length %d): ", path_len);
    for (int i = 0; i < path_len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");

    free(path);
    GraphDestroy(g);
}

int main() {
    test_shortest_path();
    return 0;
}