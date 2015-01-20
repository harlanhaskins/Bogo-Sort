//
//  main.h
//  BogoSort
//
//  Created by Harlan Haskins on 1/20/15.
//  Copyright (c) 2015 harlanhaskins. All rights reserved.
//

#include <stdlib.h>

#ifndef BogoSort_main_h
#define BogoSort_main_h

typedef struct Options {
    char *output_file;
    int trials;
    int beginning_length;
    int size;
    int single;
    int verbose;
} Options;

#endif
