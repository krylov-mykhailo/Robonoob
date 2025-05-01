#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <raylib.h>

#define MAX_SIZE 100
#define WALL '#'
#define PATH '.'
#define START 'S'
#define DEST 'D'

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

typedef struct Vertex {
    int x, y;
} Vertex;

typedef struct Graph {
    Vertex *vertices;
    int **adjMatrix;
    int numVertices;
    int posToIndex[MAX_SIZE][MAX_SIZE];
} Graph;

int isWalkable(char maze[MAX_SIZE][MAX_SIZE], int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != WALL;
}

int readMazeFromFile(char filename[], char maze[MAX_SIZE][MAX_SIZE], int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return -1;
    }

    *rows = 0;
    int expectedCols = -1;
    char line[MAX_SIZE];
    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        if (line[len - 1] == '\n') line[--len] = '\0';

        if (expectedCols == -1)
            expectedCols = len;
        else if (len != expectedCols) {
            printf("Error: Inconsistent row length at line %d (got %d, expected %d)\n", *rows + 1, len, expectedCols);
            fclose(file);
            return -1;
        }

        *cols = len;
        for (int i = 0; i < *cols; ++i)
            maze[*rows][i] = line[i];
        (*rows)++;
    }
    fclose(file);
    return 0;
}

Graph* createGraphFromMaze(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = 0;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            graph->posToIndex[i][j] = -1;

    graph->vertices = malloc(rows * cols * sizeof(Vertex));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] != WALL) {
                graph->vertices[graph->numVertices] = (Vertex){i, j};
                graph->posToIndex[i][j] = graph->numVertices;
                graph->numVertices++;
            }
        }
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
                graph->adjMatrix[i][j] = 1;
                graph->adjMatrix[j][i] = 1;
            }
        }
    }
    return graph;
}

bool DFSUtil(Graph* g, int current, int dest, bool *visited, int *path, int *length) {
    visited[current] = true;
    path[(*length)++] = current;

    if (current == dest) return true;

    for (int i = 0; i < g->numVertices; ++i) {
        if (g->adjMatrix[current][i] && !visited[i]) {
            if (DFSUtil(g, i, dest, visited, path, length)) return true;
        }
    }

    (*length)--; // backtrack
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
typedef struct Queue {
    int *data, front, rear, size;
} Queue;

Queue* createQueue(int size) {
    Queue* q = malloc(sizeof(Queue));
    q->data = malloc(size * sizeof(int));
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

void enqueue(Queue* q, int val) { q->data[q->rear++] = val; }
int dequeue(Queue* q) { return q->data[q->front++]; }
bool isEmpty(Queue* q) { return q->front == q->rear; }

void BFS(Graph* g, int start, int dest, int *path, int *length) {
    bool* visited = calloc(g->numVertices, sizeof(bool));
    int* parent = malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; ++i) parent[i] = -1;

    Queue* q = createQueue(g->numVertices);
    enqueue(q, start);
    visited[start] = true;

    bool found = false;

    while (!isEmpty(q)) {
        int curr = dequeue(q);
        if (curr == dest) {
            found = true;
            break;
        }
        for (int i = 0; i < g->numVertices; ++i) {
            if (g->adjMatrix[curr][i] && !visited[i]) {
                visited[i] = true;
                parent[i] = curr;
                enqueue(q, i);
            }
        }
    }

    if (found) {
        int len = 0, curr = dest;
        while (curr != -1) {
            path[len++] = curr;
            curr = parent[curr];
        }

        printf("BFS Path: ");
        for (int i = len - 1; i >= 0; --i)
            printf("(%d,%d) ", g->vertices[path[i]].x, g->vertices[path[i]].y);
        printf("\nLength: %d\n", len);
    } else {
        printf("No path found by BFS\n");
    }

    free(visited);
    free(parent);
    free(q->data);
    free(q);
}

void drawMazeRaylib(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols, int cellSize) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Color color;
            switch (maze[i][j]) {
                case WALL: color = BLACK; break;
                case START: color = GREEN; break;
                case DEST: color = RED; break;
                default: color = WHITE; break;
            }
            DrawRectangle(j * cellSize, i * cellSize, cellSize, cellSize, color);
            DrawRectangleLines(j * cellSize, i * cellSize, cellSize, cellSize, GRAY); // контур
        }
    }
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

int main() {
    char maze[MAX_SIZE][MAX_SIZE];
    int rows, cols;
    if (readMazeFromFile("maze.txt", maze, &rows, &cols) != 0) return 1;

    Graph* g = createGraphFromMaze(maze, rows, cols);

    int start = -1, dest = -1;
    for (int i = 0; i < g->numVertices; ++i) {
        int x = g->vertices[i].x, y = g->vertices[i].y;
        if (maze[x][y] == START) start = i;
        if (maze[x][y] == DEST) dest = i;
    }
    int path[MAX_SIZE], length = 0;
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