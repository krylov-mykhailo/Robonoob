#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x, y;
} Point;

Point* create_point(int x, int y) {
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

void destroy_point(Point* p) {
    free(p);
}

double slope_to(Point* p1, Point* p2) {
    if (p1->x == p2->x && p1->y == p2->y) return -__builtin_inf();
    if (p1->x == p2->x) return __builtin_inf();
    return (double)(p2->y - p1->y) / (p2->x - p1->x);
}

int compare_points(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->y != p2->y) return p1->y - p2->y;
    return p1->x - p2->x;
}

void find_collinear(Point* points, int N) {
    int found = 0;
    for (int i = 0; i < N - 3; i++) {
        for (int j = i + 1; j < N - 2; j++) {
            for (int k = j + 1; k < N - 1; k++) {
                for (int l = k + 1; l < N; l++) {
                    double s1 = slope_to(&points[i], &points[j]);
                    double s2 = slope_to(&points[i], &points[k]);
                    double s3 = slope_to(&points[i], &points[l]);
                    if (s1 == s2 && s2 == s3) {
                        printf("(%d, %d) -> (%d, %d) -> (%d, %d) -> (%d, %d)\n",
                               points[i].x, points[i].y,
                               points[j].x, points[j].y,
                               points[k].x, points[k].y,
                               points[l].x, points[l].y);
                        found = 1;
                    }
                }
            }
        }
    }

    if (!found) {
        printf("No collinear points found\n");
    }
}

int main() {
    int N;
    scanf("%d", &N);

    if (N < 4) {
        printf("At least 4 points are needed\n");
        return 0;
    }

    Point* points = (Point*)malloc(N * sizeof(Point));

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compare_points);

    find_collinear(points, N);

    free(points);
    return 0;
}
