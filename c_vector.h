#ifndef c_vector_h
#define c_vector_h

int* create(int size);
void push_back(int** ptr, int* size, int value);
void print(const int* ptr, int size);
void destroy(int* ptr);

#endif
