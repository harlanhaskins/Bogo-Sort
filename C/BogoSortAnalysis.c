#include "BogoSortAnalysis.h"
#include <time.h>
#include <string.h>
#include <sys/stat.h>

static char *current_time() {
    time_t rawtime;
    struct tm *timeinfo;

    const size_t buffer_size = 80;

    char *time_buffer = bs_malloc(buffer_size * sizeof(char));

    time(&rawtime);

    timeinfo = localtime(&rawtime);

    strftime(time_buffer, buffer_size, "%Y%m%dT%I%M%S%p", timeinfo);

    return time_buffer;
}

static FILE *bs_open(char *buffer) {
    FILE *output_file = fopen(buffer, "w");
    if (output_file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return output_file;
}

static FILE *file_from_options(Options *options) {
    char *buffer = malloc(256 * sizeof(char));
    char *output_dir = output_directory();

    if (!strcmp(options->output_file, "")) {
        char *timeString = current_time();
        sprintf(buffer, "%s/BogoSort_%d-trials_%d-items_%s.csv", output_dir, options->trials, options->size, timeString);
        free(timeString);
    } else {
        sprintf(buffer, "%s/%s", output_dir, options->output_file);
    }
    options->output_file = buffer;

    return bs_open(buffer);
}

static void run_analysis(Options options, FILE *output_file) {
    fprintf(output_file, "Length,Trial,Elapsed Time,Number Of Shuffles\n");
    for (size_t length = (size_t)options.beginning_length; length <= (size_t)options.size; length++) {
        for (int trial = 1; trial <= options.trials; trial++) {

            BSArray *array = bsarray_make_random(length);

            bsarray_print(array);

            clock_t start = clock();
            long long unsigned int iterations = bsarray_bogosort_v(array, options.verbose);
            clock_t end = clock();

            bsarray_print(array);
            putc('\n', stdout);

            double elapsed_time = ((double)(end - start) / CLOCKS_PER_SEC);

            fprintf(output_file, "%zu,%d,%f,%llu\n", length, trial, elapsed_time, iterations);

            bsarray_free(array);
        }
    }
    printf("Your results are available in %s\n", options.output_file);
    free(options.output_file);
    fclose(output_file);
}

void analyze(Options options) {
    FILE *output_file = file_from_options(&options);
    run_analysis(options, output_file);
}

char *output_directory() {
    char *directory = "./BogoSortResults";
    mkdir(directory, S_IRWXU);
    return directory;
}
