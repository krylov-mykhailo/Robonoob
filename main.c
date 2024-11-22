#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    char name[50];
    int num_points;
    point_t *points;
} polygon_t;

// read polygon
polygon_t read_polygon(FILE *file, err__t *err) {
    polygon_t polygon;
    int i;

    // read polygon's name
    if (fscanf(file, "%s", polygon.name) != 1) {
        polygon.num_points = -1; // Ознака кінця
        return polygon;
    }

    // read num of points
    if (fscanf(file, "%d", &polygon.num_points) != 1) {
        fprintf(stderr, "reading number of points error .\n");
        exit(EXIT_FAILURE);
    }

    // create memory for points
    polygon.points = (point_t *)malloc(polygon.num_points * sizeof(point_t));
    if (!polygon.points) {
        fprintf(stderr, "memory error for points.\n");
        exit(EXIT_FAILURE);
    }

    // read points
    for (i = 0; i < polygon.num_points; i++) {
        if (fscanf(file, "%d %d", &polygon.points[i].x, &polygon.points[i].y) != 2) {
            fprintf(stderr, "reading coordinats error.\n");
            exit(EXIT_FAILURE);
        }
    }

    return polygon;
}

// print polygon
void print_polygon(const polygon_t *polygon) {
    printf("polygon: %s\n", polygon->name);
    printf("number of points: %d\n", polygon->num_points);
    printf("points:\n");
    for (int i = 0; i < polygon->num_points; i++) {
        printf("(%d, %d)\n", polygon->points[i].x, polygon->points[i].y);
    }
    printf("\n");
}

// free memory
void free_polygon(polygon_t *polygon) {
    free(polygon->points);
}

int main() {
    FILE *file = fopen("/Users/mikhail/CLionProjects/8.1/polygons.txt", "r");
    if (!file) {
        fprintf(stderr, "open file error.\n");
        return EXIT_FAILURE;
    }

    polygon_t *polygons = NULL;
    int num_polygons = 0;

    while (1) {
        // read file polygons
        polygon_t polygon = read_polygon(file);
        if (polygon.num_points == -1) {
            break;
        }

        polygon_t *temp = realloc(polygons, (num_polygons + 1) * sizeof(polygon_t));
        if (!temp) {
            fprintf(stderr, "memory error.\n");
            fclose(file);
            free(polygons);
            return EXIT_FAILURE;
        }
        polygons = temp;

        // save polygon in massive
        polygons[num_polygons] = polygon;
        num_polygons++;
    }

    fclose(file);

    // print polygons
    for (int i = 0; i < num_polygons; i++) {
        print_polygon(&polygons[i]);
    }

    // free memory
    for (int i = 0; i < num_polygons; i++) {
        free_polygon(&polygons[i]);
    }
    free(polygons);

    return 0;
}
