#include "maze.h"
#include <stdlib.h>
#include <raylib.h>

void generateRandomMaze(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols, int numWalls) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            maze[i][j] = PATH;

    int placed = 0;
    while (placed < numWalls) {
        int x = rand() % rows;
        int y = rand() % cols;
        if (maze[x][y] == PATH) {
            maze[x][y] = WALL;
            placed++;
        }
    }

    int sx, sy, dx, dy;
    do {
        sx = rand() % rows;
        sy = rand() % cols;
    } while (maze[sx][sy] != PATH);
    maze[sx][sy] = START;

    do {
        dx = rand() % rows;
        dy = rand() % cols;
    } while ((dx == sx && dy == sy) || maze[dx][dy] != PATH);
    maze[dx][dy] = DEST;
}

void drawMazeRaylib(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols, int cellSize) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            Color color;
            switch (maze[i][j]) {
                case WALL: color = BLACK; break;
                case START: color = GREEN; break;
                case DEST: color = RED; break;
                default: color = WHITE; break;
            }
            DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, color);
            DrawRectangleLines(j * cellSize, i * cellSize, cellSize, cellSize, GRAY);
        }
}