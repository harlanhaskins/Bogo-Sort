#include "BogoSortAnalysis.h"

void analyzeBogoSort() {
    
    
    int bufferSize = 256;
    
    char buffer[bufferSize];
    
    fputs("Where would you like me to save this file? ", stdout);
    fgets(buffer, bufferSize, stdin);
    char* fileName = buffer;
    
    fputs("Up to how many items do you want to test? ", stdout);
    fgets(buffer, bufferSize, stdin);
    size_t endingLength = atoi(buffer);
    
    fputs("How many trials would you like to run? ", stdout);
    fgets(buffer, bufferSize, stdin);
    int numberOfTrials = atoi(buffer);
    
    FILE *outputFile = fopen(fileName, "w");
    
    if (outputFile == NULL) return;
    
    srand((unsigned int)time(0));

    for (size_t length = 1; length <= endingLength; length++) {
        for (int trial = 1; trial <= numberOfTrials; trial++) {
            
            int* array = randomArrayOfLength(length);
            
            clock_t start = clock();
            long long unsigned int iterations = bogoSort(array, length);
            clock_t end = clock();
            
            double elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC);
           
            fprintf(outputFile, "%zu,%d,%f,%llu\n", length, trial, elapsedTime, iterations);
            
            free(array);
        }
    }
    
    fclose(outputFile);
    
    free(fileName);
}
