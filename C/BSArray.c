//
//  BSArray.c
//  BogoSort
//
//  Created by Harlan Haskins on 1/20/15.
//  Copyright (c) 2015 harlanhaskins. All rights reserved.
//

#include "BSArray.h"
#include <stdlib.h>

void bsarray_swap(BSArray *array, int first_index, int second_index) {
    int first_number = array->contents[first_index];
    int second_number = array->contents[second_index];
    array->contents[first_index] = second_number;
    array->contents[second_index] = first_number;
}

unsigned int bsarray_is_sorted(BSArray *array) {
    for (size_t i = 1; i < array->length; i++) {
        if (array->contents[i - 1] > array->contents[i]) {
            return 0;
        }
    }
    return 1;
}


int _random_int_in_range(size_t min, size_t max) {
    double scaled = (double)rand()/ RAND_MAX;
    int random = (max - min + 1) * scaled + min;
    return random;
}

void bsarray_shuffle(BSArray *array) {
    int swap_index = 0;

    for (size_t i = array->length - 1; i > 0; --i) {
        if (array->length == 2) {
            /* There's only one possibility for an array of two objects,
               and sometimes (becasue of modulo bias) it will constantly
               switch the same index.

               Doing this means we will do the only possibility for a
               two item array.
            */
            bsarray_swap(array, 0, 1);
            return;
        }

        swap_index = _random_int_in_range(0, i);
        bsarray_swap(array, swap_index, (int)i);
    }
}

void bsarray_print_f(BSArray *array, FILE *output) {
    putc('[', output);
    for (size_t i = 0; i < array->length; i++) {
        fprintf(output, "%d", array->contents[i]);
        if (i != array->length - 1) {
            fputs(", ", output);
        }
    }
    putc(']', output);
    putc('\n', output);
}

void bsarray_print(BSArray *array) {
    bsarray_print_f(array, stdout);
}

void *bs_malloc(size_t size) {
    void *thing = malloc(size);
    if (!thing) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return thing;
}

BSArray *bsarray_make_random(size_t length) {
    BSArray *array = bs_malloc(sizeof(BSArray));
    array->contents = bs_malloc(length * sizeof(int));
    array->length = length;

    for (size_t i = 0; i < length; i++) {
        array->contents[i] = _random_int_in_range(0, length * 10);
    }

    return array;
}

void bsarray_free(BSArray *array) {
    free(array->contents);
    free(array);
}

long long unsigned bsarray_bogosort(BSArray *array) {
    return bsarray_bogosort_v(array, 0);
}

long long unsigned bsarray_bogosort_v(BSArray *array, int verbose) {
    long long unsigned iteration = 0;

    // Run a loop while the array is not sorted. This is an O(n) operation
    // running multiple millions of times. Deal with it.
    while (!bsarray_is_sorted(array)) {
        bsarray_shuffle(array);
        if (verbose) {
            bsarray_print(array);
        }
        iteration++;
    }
    return iteration;
}
