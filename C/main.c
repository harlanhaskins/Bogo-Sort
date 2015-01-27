//
//  main.c
//  BogoSort
//
//  Created by Harlan Haskins on 11/30/13.
//  Copyright (c) 2013 haskins. All rights reserved.
//

#include <string.h>
#include <limits.h>
#include <getopt.h>
#include "BogoSort.h"
#include "BogoSortAnalysis.h"

void run_with_arguments(Options options) {
    if (options.single) {
        run(options);
    } else {
        analyze(options);
    }
}

void print_usage() {
    puts("Usage: BogoSort [-s | -t trials] [-b beginning-length] [-n number-of-items] [-o filename] [-v]\n");
    exit(1);
}

static inline int clamp(unsigned long a) {
    return a < (unsigned long)INT_MAX ? (int)a : INT_MAX;
}

static inline int num_arg(char *arg) {
    return clamp(strtoul(arg, NULL, 10));
}

Options parse_arguments(int argc, char **argv) {

    Options default_options = {
        .output_file = "",
        .trials = 0,
        .beginning_length = 1,
        .size = 0,
        .single = 0,
        .verbose = 0
    };

    static struct option long_options[] = {
        {"output-file",      required_argument, 0, 'o'},
        {"trials",           required_argument, 0, 't'},
        {"beginning-length", required_argument, 0, 'b'},
        {"number-of-items",  required_argument, 0, 'n'},
        {"single",           no_argument,       0, 's'},
        {"verbose",          no_argument,       0, 'v'}
    };

    int long_index = 0;
    int option = 0;
    do {
        option = getopt_long(argc, argv, "vso:t:b:n:", long_options, &long_index);
        switch (option) {
            case 's':
                default_options.single = 1;
                break;
            case 'v':
                default_options.verbose = 1;
                break;
            case 'o':
                default_options.output_file = optarg;
                break;
            case 't':
                default_options.trials = num_arg(optarg);
                break;
            case 'b':
                default_options.beginning_length = num_arg(optarg);
                break;
            case 'n':
                default_options.size = num_arg(optarg);
                break;
            default:
                break;
        }
    } while (option != -1);

    if (!(default_options.single ^ default_options.trials) ||
         (default_options.size) == 0) {
        print_usage();
    }

    return default_options;
}

int main(int argc, char **argv) {
    Options options = parse_arguments(argc, argv);
    run_with_arguments(options);
    return EXIT_SUCCESS;
}

