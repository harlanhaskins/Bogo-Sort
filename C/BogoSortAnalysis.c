#include "BogoSortAnalysis.h"

size_t stringLength(char* string) {
    int i = 0;
    while (string[i] != '\0') i++;
    return i;
}

void analyzeBogoSort() {
    
    int bufferSize = 256;
    
    char buffer[bufferSize];
    
    fputs("Up to how many items do you want to test? ", stdout);
    fgets(buffer, bufferSize, stdin);
    size_t endingLength = atoi(buffer);
    
    fputs("How many trials would you like to run? ", stdout);
    fgets(buffer, bufferSize, stdin);
    int numberOfTrials = atoi(buffer);
    
    time_t rawtime;
    struct tm * timeinfo;
    char timeBuffer[80];
    
    time ( &rawtime );
    
    timeinfo = localtime ( &rawtime );
    
    strftime (timeBuffer, 80, "%Y%m%dT%I%M%S%p", timeinfo);
    
    sprintf(buffer, "BogoSort_%d-trials_%zu-items_%s.csv", numberOfTrials, endingLength, timeBuffer);
    
    FILE* outputFile = fopen(buffer, "w");
    
    if (outputFile == NULL) return;
    
    fprintf(outputFile, "Length,Trial,Elapsed Time,Number Of Shuffles\n");
    
    srand((unsigned int)time(NULL));

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
    
    printf("\nYour results are available in %s\n", buffer);
}
