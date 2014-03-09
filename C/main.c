//
//  main.c
//  BogoSort
//
//  Created by Harlan Haskins on 11/30/13.
//  Copyright (c) 2013 haskins. All rights reserved.
//

#include <string.h>
#include "BogoSort.h"
#include "BogoSortAnalysis.h"

void runWithArguments(Options options) {
    if (options.isSingleSort) {
        runBogoSort(options.endingLength);
    }
    else {
        analyzeBogoSort(options);
    }
}

void printUsage() {
    puts("Usage: BogoSort [-s | -t numberOfTests] [-b beginningLength] [-e endingLength | -n numberOfItems] [-o filename]\n");
    abort();
}

Options parseArguments(int argc, char** argv) {

    Options defaultOptions = {
        .outputFile = "",
        .numberOfTests = 0,
        .beginningLength = 1,
        .endingLength = 0,
        .isSingleSort = 0
    };

    for (int i = 1; i < argc; i++) {
        char* currentArgument = argv[i];
        if (strcmp(currentArgument, "-o") == 0 || strcmp(currentArgument, "--output-file") == 0) {
            if (i == (argc - 1) || argv[i + 1][0] == '-') {
                printUsage();
            }
            i++;
            defaultOptions.outputFile = argv[i];
        }
        else if (strcmp(currentArgument, "-t") == 0 || strcmp(currentArgument, "--trials") == 0) {
            if (i == (argc - 1) || argv[i + 1][0] == '-' || defaultOptions.isSingleSort) {
                printUsage();
            }
            i++;
            defaultOptions.numberOfTests = strtoul(argv[i], NULL, 10);
        }
        else if (strcmp(currentArgument, "-b") == 0 || strcmp(currentArgument, "--beginning-length") == 0) {
            if (i == (argc - 1) || argv[i + 1][0] == '-') {
                printUsage();
            }
            i++;
            defaultOptions.beginningLength = strtoul(argv[i], NULL, 10);
        }
        else if (strcmp(currentArgument, "-n") == 0 || strcmp(currentArgument, "--number") == 0 || strcmp(currentArgument, "-e") == 0 || strcmp(currentArgument, "--ending-length") == 0) {
            if (i == (argc - 1) || argv[i + 1][0] == '-') {
                printUsage();
            }
            i++;
            defaultOptions.endingLength = strtoul(argv[i], NULL, 10);
        }
        else if (strcmp(currentArgument, "-s") == 0 || strcmp(currentArgument, "--single") == 0) {
            if (defaultOptions.numberOfTests) {
                printUsage();
            }
            defaultOptions.isSingleSort = 1;
        }
        else {
            printUsage();
        }
    }
    if (!defaultOptions.isSingleSort && !defaultOptions.numberOfTests) {
        printUsage();
    }
    return defaultOptions;
}

int main(int argc, char** argv) {
    Options options = parseArguments(argc, argv);
    runWithArguments(options);
    return 0;
}

