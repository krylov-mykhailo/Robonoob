#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

Point p0;

int compare_points(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->y == p2->y)
        return p1->x - p2->x;
    return p1->y - p2->y;
}

double getAngle(Point p0, Point p) {
    return atan2(p.y - p0.y, p.x - p0.x);
}

int compare_by_polar_angle(const void *a, const void *b) {
    Point *pointA = (Point *)a;
    Point *pointB = (Point *)b;
    double angleA = getAngle(p0, *pointA);
    double angleB = getAngle(p0, *pointB);
    return (angleA > angleB) - (angleA < angleB);
}

int ccw(Point a, Point b, Point c) {
    int area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area2 < 0)
        return -1;
    else if (area2 > 0)
        return 1;
    else
        return 0;
}

int convexHull(Point points[], int n, Point result[]) {
    if (n < 3) return 0;

    qsort(points, n, sizeof(Point), compare_points);
    p0 = points[0];
    qsort(points + 1, n - 1, sizeof(Point), compare_by_polar_angle);

    Point hull[n];
    int hullSize = 0;
    hull[hullSize++] = points[0];
    hull[hullSize++] = points[1];

    for (int i = 2; i < n; i++) {
        while (hullSize >= 2 && ccw(hull[hullSize - 2], hull[hullSize - 1], points[i]) <= 0) {
            hullSize--;
        }
        hull[hullSize++] = points[i];
    }

    for (int i = 0; i < hullSize; i++) {
        result[i] = hull[i];
    }
    return hullSize;
}

void printHull(Point result[], int hullSize) {
    for (int i = 0; i < hullSize; i++) {
        printf("(%d, %d)\n", result[i].x, result[i].y);
    }
}

int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    if (n < 3) {
        printf("Cannot be formed with less than 3 points.\n");
        return 1;
    }

    Point points[n];
    printf("Enter the points as x y pairs:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    Point result[n];
    int size = convexHull(points, n, result);

    printf("Convex Hull:\n");
    printHull(result, size);

    return 0;
}
