#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "maze.h"
#include "graph.h"
#include "dfs.h"
#include "bfs.h"
int main() {
    srand(time(NULL));

    char maze[MAX_SIZE][MAX_SIZE];
    int rows, cols, numWalls;
    printf("Enter maze size (rows cols): ");
    scanf("%d %d", &rows, &cols);

    int totalCells = rows * cols;
    int maxObstacles = totalCells - 2;

    do {
        printf("Enter number of obstacles (max %d): ", maxObstacles);
        scanf("%d", &numWalls);
        if (numWalls > maxObstacles) {
            printf("Too many obstacles! Try a lower number.\n");
        }
    } while (numWalls > maxObstacles);

    generateRandomMaze(maze, rows, cols, numWalls);

    Graph* g = createGraphFromMaze(maze, rows, cols);

    int start = -1, dest = -1;
    for (int i = 0; i < g->numVertices; ++i) {
        int x = g->vertices[i].x, y = g->vertices[i].y;
        if (maze[x][y] == START) start = i;
        if (maze[x][y] == DEST) dest = i;
    }

    int path[MAX_SIZE * MAX_SIZE], length = 0;
    if (start != -1 && dest != -1) {
        DFS(g, start, dest, path, &length);
        BFS(g, start, dest, path, &length);
    } else {
        printf("Start or destination not found in maze.\n");
    }

    const int cellSize = 30;
    int screenWidth = cols * cellSize;
    int screenHeight = rows * cellSize;

    InitWindow(screenWidth, screenHeight, "Maze Visualization with raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawMazeRaylib(maze, rows, cols, cellSize);
        drawPathRaylib(g, path, length, cellSize);

        EndDrawing();
    }

    CloseWindow();
    freeGraph(g);
    return 0;
}