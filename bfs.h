#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include "paths_helper.h"

PathsPtr bfs(const GraphPtr g, vertex_t s);
vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len);

#endif