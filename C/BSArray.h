//
//  BSArray.h
//  BogoSort
//
//  Created by Harlan Haskins on 1/20/15.
//  Copyright (c) 2015 harlanhaskins. All rights reserved.
//

#ifndef BSArray_h
#define BSArray_h

#include <stdio.h>

typedef struct {
    int *contents;
    size_t length;
} BSArray;

extern void *bs_malloc(size_t size);

extern BSArray *bsarray_make_random(size_t length);
extern void bsarray_free(BSArray *array);

extern void bsarray_print(BSArray *array);

extern void bsarray_print_f(BSArray *array, FILE *outputfile);

extern void bsarray_swap(BSArray *array, int first_index, int second_index);

extern unsigned int bsarray_is_sorted(BSArray *array);

extern void bsarray_shuffle(BSArray *array);

extern long long unsigned int bsarray_bogosort(BSArray *array, int verbose);

#endif
