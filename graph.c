#include "graph.h"
#include <stdlib.h>
#include <raylib.h>

int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int isWalkable(char maze[MAX_SIZE][MAX_SIZE], int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != WALL;
}

Graph* createGraphFromMaze(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = 0;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            graph->posToIndex[i][j] = -1;

    graph->vertices = malloc(rows * cols * sizeof(Vertex));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (maze[i][j] != WALL) {
                graph->vertices[graph->numVertices] = (Vertex){i, j};
                graph->posToIndex[i][j] = graph->numVertices++;
            }

    graph->adjMatrix = malloc(graph->numVertices * sizeof(int*));
    for (int i = 0; i < graph->numVertices; ++i)
        graph->adjMatrix[i] = calloc(graph->numVertices, sizeof(int));

    for (int i = 0; i < graph->numVertices; ++i) {
        int x = graph->vertices[i].x, y = graph->vertices[i].y;
        for (int d = 0; d < 4; ++d) {
            int nx = x + directions[d][0], ny = y + directions[d][1];
            if (isWalkable(maze, nx, ny, rows, cols)) {
                int j = graph->posToIndex[nx][ny];
                graph->adjMatrix[i][j] = graph->adjMatrix[j][i] = 1;
            }
        }
    }

    return graph;
}

void drawPathRaylib(Graph* g, int* path, int length, int cellSize) {
    for (int i = 0; i < length; ++i) {
        int x = g->vertices[path[i]].x;
        int y = g->vertices[path[i]].y;
        DrawRectangle(y * cellSize, x * cellSize, cellSize, cellSize, BLUE);
    }
}

void freeGraph(Graph* g) {
    for (int i = 0; i < g->numVertices; ++i)
        free(g->adjMatrix[i]);
    free(g->adjMatrix);
    free(g->vertices);
    free(g);
}