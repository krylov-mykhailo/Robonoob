#ifndef DYNAMIC_2D_ARRAY_H
#define DYNAMIC_2D_ARRAY_H

char** allocate_2d_array(int size);
int fill_2d_array(char** arr, int size);
void print_2d_array(const char** arr, int size);
void sort_2d_array(char** arr, int size);
void sort_rows(char** arr, int size);
void free_2d_array(char** arr, int size);

#endif // DYNAMIC_2D_ARRAY_H

