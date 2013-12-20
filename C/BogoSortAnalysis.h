//
//  BogoSortAnalysis.h
//  BogoSort
//
//  Created by Harlan Haskins on 11/30/13.
//  Copyright (c) 2013 haskins. All rights reserved.
//

#include "BogoSort.h"
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#ifndef BogoSort_BogoSortAnalysis_h
#define BogoSort_BogoSortAnalysis_h

typedef struct Options {
    char* outputFile;
    int numberOfTests;
    int beginningLength;
    int endingLength;
    int isSingleSort;

} Options;

void analyzeBogoSort(Options options);
char* outputDirectory();

#endif
