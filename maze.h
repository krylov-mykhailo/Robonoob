#ifndef MAZE_H
#define MAZE_H

#define MAX_SIZE 100
#define WALL '#'
#define PATH '.'
#define START 'S'
#define DEST 'D'

void generateRandomMaze(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols, int numWalls);
void drawMazeRaylib(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols, int cellSize);

#endif