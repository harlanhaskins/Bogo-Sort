//
//  main.c
//  BogoSort
//
//  Created by Harlan Haskins on 11/30/13.
//  Copyright (c) 2013 haskins. All rights reserved.
//

#include <stdio.h>
#include "BogoSort.h"
#include "BogoSortAnalysis.h"

void printMenu() {
    puts("Welcome to BogoSort. Please enter the number of what you'd like to do.\n");
    puts("\t1. Run a BogoSort");
    puts("\t2. Save a series of BogoSorts");
    puts("\t3. Quit\n");
    
    fputs("What would you like to do? ", stdout);
    
    int bufferSize = 256;
    
    char buffer[bufferSize];
    
    fgets (buffer, bufferSize, stdin);
    int menuChoice = atoi(buffer);
    
    putchar('\n');
    
    switch (menuChoice) {
        case 1: {
            runBogoSort();
            putchar('\n');
            printMenu();
            break;
        }
        case 2: {
            analyzeBogoSort();
            putchar('\n');
            printMenu();
            break;
        }
        default:
            return;
    }
}

int main()
{
    printMenu();
    return 0;
}

