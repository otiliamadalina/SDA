#include <stdio.h>
#include "fib_algs.h"
#include "sort_algs.h"
#include "search_algs.h"
#include <time.h>
#include <stdlib.h>

/*
 * 51485628397465928374 +
 *      103485234856234
 * ____________________
 *                    8
 *
 *
 *  char s1[] = "51485628397465928374";
 *  char s2[] = "23485234856234";
 *  char s3[] = "508";
 * */

/*
 * Bubble sort
 * 1 2 3 4 5 6 7 8
 * 3 5 6 2 4 8 9 1
 * 8 7 6 5 4 3 2 1
 */

/*
 *
 * Quick sort
 *
 * 1 2 3 4 5 6 7 8
 * 3 5 6 2 4 8 9 1
 * 5 3 6 2 8 4 9 1
 *
 * */

#define GET_EXEC_TIME(x) for(clock_t start_time = clock(), run = start_time; run == start_time; run = clock(), x=(double)( (clock() - start_time) / (double)CLOCKS_PER_SEC ))

int generate_random_number() {
    return (rand() % 10);
}

int *generate_random_array(int array_size) {
    int *result_array = (int *) malloc(sizeof(int) * array_size);
    for (int i = 0; i < array_size; i++) {
        result_array[i] = generate_random_number();
    }
    return result_array;
}

void print_array(int *array, int array_size) {
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

double get_exec_time_in_sec_of_fib_alg(int fibo_nr) {
    clock_t start_time = clock();
    fibbonacci(fibo_nr);
    clock_t end_time = clock();
    return (end_time - start_time) / (double) CLOCKS_PER_SEC;
}

double get_exec_time_in_sec_of_sort_alg(int array_size, void (*sort_fun)(int *, int)) {
    int *random_array = generate_random_array(array_size);
    //print_array(random_array, array_size);
    clock_t start_time = clock();
    sort_fun(random_array, array_size);
    clock_t end_time = clock();

    free(random_array);
    return (end_time - start_time) / (double) CLOCKS_PER_SEC;
}

double get_exec_time_in_sec_of_search_alg(int array_size, int search_key, int (*search_fun)(int *, int, int)) {
    int *random_array = generate_random_array(array_size);
    //print_array(random_array, array_size);
    //bubble_sort(random_array, array_size);
    clock_t start_time = clock();
    search_fun(random_array, array_size, search_key);
    clock_t end_time = clock();

    free(random_array);
    return (end_time - start_time) / (double) CLOCKS_PER_SEC;
}


int main() {
    srand(time(NULL));
    for(int i = 37; i <= 47; i+=2) {
       printf("Time to execute fibo(%d) = %lf\n",i, get_exec_time_in_sec_of_fib_alg(i));
    }

    printf("----------------------------Sort algs-----------------------------\n");
    printf("Merge sort\n");
    for (int i = 100; i <= 100000; i *= 10) {
        printf("Time to execute sort(%d) = %lf\n", i, get_exec_time_in_sec_of_sort_alg(i, merge_sort));
    }


    printf("\nBubble sort\n");
    for (int i = 100; i <= 100000; i *= 10) {
        printf("Time to execute sort(%d) = %lf\n", i, get_exec_time_in_sec_of_sort_alg(i, bubble_sort));
    }

    printf("----------------------------Search algs-----------------------------\n");
    printf("Linear search\n");
    for (int i = 10000; i <= 100000000; i *= 10) {
        printf("Time to execute search(%d) = %lf\n", i, get_exec_time_in_sec_of_search_alg(i, 11, linear_search));
    }


    printf("Sentinel search\n");
    for (int i = 10000; i <= 1000000000; i *= 10) {
        printf("Time to execute search(%d) = %lf\n", i, get_exec_time_in_sec_of_search_alg(i, 11, sentinel_search));
    }

    return 0;
}