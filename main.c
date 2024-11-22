#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void generate_random_array(int arr[], int size);
void print_array(const int arr[], int size);
void bubble_sort(int arr[], int size);
int binary_search_recursive(const int arr[], int low, int high, int value);
int binary_search_loop(const int arr[], int size, int value);

int main() {
    int arr[SIZE];
    int value, result;

    srand(time(NULL));

    generate_random_array(arr, SIZE);
    printf("Згенерований масив:\n");
    print_array(arr, SIZE);

    printf("\nВведіть число для пошуку: ");
    scanf("%d", &value);

    bubble_sort(arr, SIZE);
    printf("\nВідсортований масив:\n");
    print_array(arr, SIZE);

    result = binary_search_recursive(arr, 0, SIZE - 1, value);
    if (result != -1) {
        printf("\nЧисло %d знайдено на індексі %d.\n", value, result);
    } else {
        printf("\nЧисло %d не знайдено.\n", value);
    }

    result = binary_search_loop(arr, SIZE, value);
    if (result != -1) {
        printf("\nЧисло %d знайдено на індексі %d.\n", value, result);
    } else {
        printf("\nЧисло %d не знайдено.\n", value);
    }

    return 0;
}

void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

void print_array(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binary_search_recursive(const int arr[], int low, int high, int value) {
    if (low > high) {
        return -1;
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] == value) {
        return mid;
    } else if (arr[mid] > value) {
        return binary_search_recursive(arr, low, mid - 1, value);
    } else {
        return binary_search_recursive(arr, mid + 1, high, value);
    }
}

int binary_search_loop(const int arr[], int size, int value) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] > value) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}
