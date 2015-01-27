// Include the header.
#include "BogoSort.h"
#include <time.h>
#include <locale.h>

// Set some constants to use to calculate the number of hours,
// minutes, etc.
static const int SECONDS_PER_MINUTE = 60;
static const int SECONDS_PER_HOUR   = SECONDS_PER_MINUTE * 60;

char *_formatted_time(double time) {
    int hours = (time / SECONDS_PER_HOUR);
    time -= (hours * SECONDS_PER_HOUR);

    int minutes = (time / SECONDS_PER_MINUTE);
    time -= (minutes * SECONDS_PER_MINUTE);

    size_t time_length = 17; // strlen("00:00:00.000000\n")
    char *time_string = bs_malloc(time_length);

    snprintf(time_string, time_length, "%02d:%02d:%f", hours, minutes, time);

    return time_string;
}

void run(Options options) {
    // Seed the random number generator.
    srand((unsigned int)time(NULL));

    BSArray *array = bsarray_make_random(options.size);

    bsarray_print(array);
    clock_t start = clock();
    long long unsigned int iteration_count = bsarray_bogosort_v(array, options.verbose);
    clock_t end = clock();
    bsarray_print(array);

    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    char *time_string = _formatted_time(elapsed);
    printf("It took me %s to BogoSort this list.\n", time_string);
    free(time_string);
    
    // Set the locale to LC_NUMERIC so we can use the ' flag in our format.
    setlocale(LC_NUMERIC, "");
    char *times_string = iteration_count == 1 ? "time" : "times";
    printf("I shuffled it %'llu %s.\n", iteration_count, times_string);

    double shuffles_per_sec = iteration_count / elapsed;
    printf("That's %.2f shuffles per second.\n", shuffles_per_sec);

    bsarray_free(array);
}
