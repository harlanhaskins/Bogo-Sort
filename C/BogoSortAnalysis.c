#include "BogoSortAnalysis.h"

static char* currentTimeString() {
    time_t rawtime;
    struct tm *timeinfo;

    const size_t BUFFER_SIZE = 80;

    char *timeBuffer = cautiousMalloc(BUFFER_SIZE * sizeof(char));

    time(&rawtime);

    timeinfo = localtime(&rawtime);

    strftime(timeBuffer, BUFFER_SIZE, "%Y%m%dT%I%M%S%p", timeinfo);

    return timeBuffer;
}

static FILE* cautiousOpen(char* buffer) {
    FILE* outputFile = fopen(buffer, "w");
    if (outputFile == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return outputFile;
}

static FILE* fileFromOptions(Options *options) {
    char *buffer = malloc(256 * sizeof(char));
    char *outputDir = outputDirectory();

    if (!strcmp(options->outputFile, "")) {
        char *timeString = currentTimeString();
        sprintf(buffer, "%s/BogoSort_%d-trials_%d-items_%s.csv", outputDir, options->trials, options->size, timeString);
        free(timeString);
    }
    else {
        sprintf(buffer, "%s/%s", outputDir, options->outputFile);
    }
    options->outputFile = buffer;

    return cautiousOpen(buffer);
}

static void runAnalysis(Options options, FILE *outputFile) {
    fprintf(outputFile, "Length,Trial,Elapsed Time,Number Of Shuffles\n");
    for (size_t length = (size_t)options.beginningLength; length <= (size_t)options.size; length++) {
        for (int trial = 1; trial <= options.trials; trial++) {

            int* array = randomArrayOfLength(length);

            printArray(array, length);

            clock_t start = clock();
            long long unsigned int iterations = bogoSort(array, length, options.verbose);
            clock_t end = clock();

            printArray(array, length);
            putc('\n', stdout);

            double elapsedTime = ((double)(end - start) / CLOCKS_PER_SEC);

            fprintf(outputFile, "%zu,%d,%f,%llu\n", length, trial, elapsedTime, iterations);

            free(array);
        }
    }
    printf("Your results are available in %s\n", options.outputFile);
    free(options.outputFile);
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
