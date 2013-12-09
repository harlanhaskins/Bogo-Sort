#include "BogoSortAnalysis.h"

size_t stringLength(char* string) {
    int i = 0;
    while (string[i] != '\0') i++;
    return i;
}

void analyzeBogoSort(Options options) {
    
    time_t rawtime;
    struct tm * timeinfo;
    char timeBuffer[80];
    
    time ( &rawtime );
    
    timeinfo = localtime ( &rawtime );
    
    strftime (timeBuffer, 80, "%Y%m%dT%I%M%S%p", timeinfo);
    
    char* outputDir = outputDirectory();
    
    char buffer[256];
    if (!strcmp(options.outputFile, "")) {
        sprintf(buffer, "%s/BogoSort_%d-trials_%d-items_%s.csv", outputDir, options.numberOfTests, options.highestLength, timeBuffer);
        options.outputFile = buffer;
    }
    else {
        sprintf(buffer, "%s/%s", outputDir, options.outputFile);
        options.outputFile = buffer;
    }
    
    FILE* outputFile = fopen(buffer, "w");
    
    if (outputFile == NULL) return;
    
    fprintf(outputFile, "Length,Trial,Elapsed Time,Number Of Shuffles\n");
    
    srand((unsigned int)time(NULL));

    for (size_t length = 1; length <= (size_t)options.highestLength; length++) {
        for (int trial = 1; trial <= options.numberOfTests; trial++) {
            
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
    
    printf("\nYour results are available in %s\n", options.outputFile);
}

char* outputDirectory() {
    char* directory = "./BogoSortResults";
    mkdir(directory, S_IRWXU);
    return directory;
}
