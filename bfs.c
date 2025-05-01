#include "bfs.h"
#include "queue.h"

void bfs_search(const GraphPtr g, PathsPtr p, vertex_t s) {
    QueuePtr q = QueueInit();
    p->marked[s] = 1;
    enqueue(q, s);

    while (!QueueEmpty(q)) {
        vertex_t v = dequeue(q);
        int size = 0;
        const vertex_t *adj = GraphAdj(g, v, &size);

        for (int i = 0; i < size; i++) {
            vertex_t w = adj[i];
            if (!p->marked[w]) {
                enqueue(q, w);
                p->marked[w] = 1;
                p->edge_to[w] = v;
            }
        }
    }

    QueueDestroy(q);
}

PathsPtr bfs(const GraphPtr g, vertex_t s) {
    PathsPtr p = fromGraph(g, s);
    bfs_search(g, p, s);
    return p;
}