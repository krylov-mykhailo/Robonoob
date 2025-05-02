#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int vertex_t;

typedef struct Node {
    vertex_t vertex;
    struct Node* next;
} Node;

typedef struct {
    int V;
    Node** adj;
} Digraph;
typedef Digraph* DigraphPtr;

DigraphPtr create_digraph(int V) {
    DigraphPtr g = malloc(sizeof(Digraph));
    g->V = V;
    g->adj = malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void add_edge(DigraphPtr g, vertex_t from, vertex_t to) {
    Node* node = malloc(sizeof(Node));
    node->vertex = to;
    node->next = g->adj[from];
    g->adj[from] = node;
}

void free_graph(DigraphPtr g) {
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adj[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

typedef struct Stack {
    vertex_t* data;
    int top;
    int capacity;
} Stack;

Stack* create_stack(int capacity) {
    Stack* stack = malloc(sizeof(Stack));
    stack->data = malloc(sizeof(vertex_t) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack* stack, vertex_t v) {
    stack->data[++stack->top] = v;
}

vertex_t pop(Stack* stack) {
    return stack->data[stack->top--];
}

void free_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

void dfs(const DigraphPtr g, int v, bool* marked, Stack* reverse_post) {
    marked[v] = true;
    for (Node* node = g->adj[v]; node != NULL; node = node->next) {
        int w = node->vertex;
        if (!marked[w]) {
            dfs(g, w, marked, reverse_post);
        }
    }
    push(reverse_post, v);
}

vertex_t* topological_sort(const DigraphPtr g) {
    bool* marked = calloc(g->V, sizeof(bool));
    Stack* reverse_post = create_stack(g->V);

    for (int v = 0; v < g->V; ++v) {
        if (!marked[v]) {
            dfs(g, v, marked, reverse_post);
        }
    }

    vertex_t* order = malloc(sizeof(vertex_t) * g->V);
    for (int i = 0; i < g->V; ++i) {
        order[i] = pop(reverse_post);
    }

    free(marked);
    free_stack(reverse_post);
    return order;
}

int main() {
    DigraphPtr g = create_digraph(7);
    add_edge(g, 0, 5);
    add_edge(g, 0, 2);
    add_edge(g, 0, 1);
    add_edge(g, 1, 4);
    add_edge(g, 5, 2);
    add_edge(g, 3, 5);
    add_edge(g, 3, 4);
    add_edge(g, 3, 2);
    add_edge(g, 3, 6);
    add_edge(g, 6, 4);
    add_edge(g, 6, 0);
    vertex_t* order = topological_sort(g);

    printf("Topological order: ");
    for (int i = 0; i < g->V; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");

    free(order);
    free_graph(g);
    return 0;
}