//
// Created by ASUS on 31.05.2024.
//

#include <stdbool.h>

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(int *array, int array_size)
{
    int i, j;
    bool is_swapped;
    for (i = 0; i < array_size - 1; i++) {
        is_swapped = false;
        for (j = 0; j < array_size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                is_swapped = true;
            }
        }
        if (is_swapped == false)
            break;
    }
}

void _merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void _merge_sort(int* arr, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        _merge_sort(arr, l, m);
        _merge_sort(arr, m + 1, r);

        _merge(arr, l, m, r);
    }
}


void merge_sort(int *array, int array_size) {
    _merge_sort(array, 0, array_size - 1);
}