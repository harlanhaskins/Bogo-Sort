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

#if __has_extension(blocks)
#include <Block.h>
#endif

#include "BogoSort.h"
#include "BogoSortAnalysis.h"

void runWithArguments(Options options) {
    if (options.single) {
        runBogoSort(options.size, options.verbose);
    }
    else {
        analyzeBogoSort(options);
    }
}

void printUsage() {
    puts("Usage: BogoSort [-s | -t trials] [-b beginning-length] [-n number-of-items] [-o filename] [-v]\n");
    exit(1);
}

static inline int clamp(unsigned long a) {
    return a < (unsigned long)INT_MAX ? (int)a : INT_MAX;
}

Options parseArguments(int argc, char** argv) {

    Options defaultOptions = {
        .outputFile = "",
        .trials = 0,
        .beginningLength = 1,
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

    int longIndex = 0;
    int option = 0;
    do {
        option = getopt_long(argc, argv, "vso:t:b:n:", long_options, &longIndex);
        switch (option) {
            case 's':
                defaultOptions.single = 1;
                break;
            case 'v':
                defaultOptions.verbose = 1;
                break;
            case 'o':
                defaultOptions.outputFile = optarg;
                break;
            case 't':
                defaultOptions.trials = clamp(strtoul(optarg, NULL, 10));
                break;
            case 'b':
                defaultOptions.beginningLength = clamp(strtoul(optarg, NULL, 10));
                break;
            case 'n':
                defaultOptions.size = clamp(strtoul(optarg, NULL, 10));
                break;
            default:
                break;
        }
    } while (option != -1);

    if ((!defaultOptions.single && !defaultOptions.trials)  ||
         (defaultOptions.single && defaultOptions.trials)   ||
         (defaultOptions.size) == 0) {
        printUsage();
    }

    return defaultOptions;
}

int main(int argc, char** argv) {
    Options options = parseArguments(argc, argv);
    runWithArguments(options);
    return 0;
}

