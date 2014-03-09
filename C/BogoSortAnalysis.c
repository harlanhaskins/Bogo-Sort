#include "BogoSortAnalysis.h"

char* currentTimeString() {
    time_t rawtime;
    struct tm *timeinfo;

    const size_t BUFFER_SIZE = 80;

    char *timeBuffer = cautiousMalloc(BUFFER_SIZE * sizeof(char));

    time(&rawtime);

    timeinfo = localtime(&rawtime);

    strftime(timeBuffer, BUFFER_SIZE, "%Y%m%dT%I%M%S%p", timeinfo);

    return timeBuffer;
}

FILE* cautiousOpen(char* buffer) {
    FILE* outputFile = fopen(buffer, "w");
    if (outputFile == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return outputFile;
}

FILE* fileFromOptions(Options *options) {
    char buffer[256];
    char *outputDir = outputDirectory();

    if (!strcmp(options->outputFile, "")) {
        char *timeString = currentTimeString();
        sprintf(buffer, "%s/BogoSort_%d-trials_%d-items_%s.csv", outputDir, options->numberOfTests, options->endingLength, timeString);
        free(timeString);
    }
    else {
        sprintf(buffer, "%s/%s", outputDir, options->outputFile);
    }
    options->outputFile = buffer;

    return cautiousOpen(buffer);
}

void runAnalysis(Options options, FILE *outputFile) {
    fprintf(outputFile, "Length,Trial,Elapsed Time,Number Of Shuffles\n");
    for (size_t length = (size_t)options.beginningLength; length <= (size_t)options.endingLength; length++) {
        for (int trial = 1; trial <= options.numberOfTests; trial++) {

            int* array = randomArrayOfLength(length);

            printArray(array, length);

            clock_t start = clock();
            long long unsigned int iterations = bogoSort(array, length);
            clock_t end = clock();

            printArray(array, length);
            putc('\n', stdout);

            double elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC);

            fprintf(outputFile, "%zu,%d,%f,%llu\n", length, trial, elapsedTime, iterations);

            free(array);
        }
    }
    //printf("\nYour results are available in %s\n", options.outputFile);

    fclose(outputFile);
}

void analyzeBogoSort(Options options) {
    FILE *outputFile = fileFromOptions(&options);
    runAnalysis(options, outputFile);
}

char* outputDirectory() {
    char* directory = "./BogoSortResults";
    mkdir(directory, S_IRWXU);
    return directory;
}
