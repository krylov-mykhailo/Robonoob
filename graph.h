#ifndef GRAPH_H
#define GRAPH_H

#include "maze.h"

typedef struct {
    int x, y;
} Vertex;

typedef struct {
    Vertex *vertices;
    int **adjMatrix;
    int numVertices;
    int posToIndex[MAX_SIZE][MAX_SIZE];
} Graph;

int isWalkable(char maze[MAX_SIZE][MAX_SIZE], int x, int y, int rows, int cols);
Graph* createGraphFromMaze(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols);
void drawPathRaylib(Graph* g, int* path, int length, int cellSize);
void freeGraph(Graph* g);

#endif