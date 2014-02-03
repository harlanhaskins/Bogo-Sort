// Include the header.
#include "BogoSort.h"

void swap(int *array, int firstIndex, int secondIndex, size_t length) {

    int largestIndex = (length - 1);
    if (firstIndex > largestIndex || secondIndex > largestIndex) {
        printf("Error - Invalid Random Index: %d or %d is greater than %d\n",
                firstIndex, secondIndex, largestIndex);
        exit(EXIT_FAILURE);
    }

    // Create a temp variable to store the first index, because we'll
    // be overwriting it.
    int firstNumber = array[firstIndex];
    int secondNumber = array[secondIndex];

    // Set the value at the first index to the value at the second index.
    array[firstIndex] = secondNumber;

    // Set the value at the second index to the value of the first index.
    array[secondIndex] = firstNumber;
}

unsigned int isSorted(int* array, size_t length) {
    // Iterate through the array.
    for (size_t i = 1; i < length; i++) {
        // If at any point the previous array item is greater than (or
        // less than, in the case of descending arrays, return false.
        if (array[i - 1] > array[i]) {
            return 0;
        }
    }
    // If the for loop exited successfully, return true.
    return 1;
}

int randomIntegerInRange(int min, int max)
{
    double scaled = (double)rand( )/ RAND_MAX;

    int random = (max - min + 1) * scaled + min;

    if (random > max) {
        printf("Error: Random number too high.\n");
        abort();
    }

    return random;
}

void shuffleArray(int* array, size_t length) {

    // Declare and initialize the two indices that will be used to swap.
    int firstIndex = 0;
    int secondIndex = 0;

    // Iterate through the array.
    for (size_t i = 0; i < length; i++) {
        if (length == 2) {
            /* There's only one possibility for an array of two objects,
               and sometimes (becasue of modulo bias) it will constantly
               switch the same index.

               Doing this means we will do the only possibility for a
               two item array.
            */
            swap(array, 0, 1, length);
            return;
        }
        // Reset the first index to some random number.
        firstIndex = randomIntegerInRange(0, (length - 1));
        secondIndex = randomIntegerInRange(0, (length - 1));

        // Run the swap function with the two random indices.
        swap(array, firstIndex, secondIndex, length);
    }
}

void printArrayToFile(int* array, size_t length, FILE *output) {
    // Print a bracket (for pretty printing.)
    putc('[', output);

    // Iterate through the numbers in the array.
    for (size_t i = 0; i < length; i++) {
        // Print the number at the current index
        fprintf(output, "%d", array[i]);

        // If the number is not the last number in the array...
        if (i != length - 1) {
            // ...then print a comma and a space after it.
            fputs(", ", output);
        }
    }
    // Print the closing bracket and the newline character.
    putc(']', output);
    putc('\n', output);
}

void printArray(int* array, size_t length) {
    printArrayToFile(array, length, stdout);
}

void* cautiousMalloc(size_t size) {
    void* thing = malloc(size);
    if (!thing) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return thing;
}

int* randomArrayOfLength(size_t length) {
    // Allocate an array of the length specified.
    int *array = cautiousMalloc((int)length * sizeof(int));

    // Iterate (length) times.
    for (size_t i = 0; i < length; i++) {
        // Add a random number from 0 to (length * 10).
        array[i] = randomIntegerInRange(0, length * 10);
    }

    // Return the random array.
    return array;
}

long long unsigned int bogoSort(int* array, size_t length) {
    // Initialize a number of iterations.
    long long unsigned int iteration = 0;

    // Run a loop while the array is not sorted. This is an O(n) operation
    // running multiple millions of times. Deal with it.
    while (!isSorted(array, length)) {
        // If you're in this loop, congratulations, the list isn't sorted.

        // Shuffle the array.
        shuffleArray(array, length);

        // Optionally print the array each time.
        // printArray(array, length);

        // Add to the iteration counter.
        iteration++;
    }

    // Once you're here, the list is sorted and you can return the number
    // of iterations it took.
    return iteration;
}

char* formattedTimeFromDouble(double time) {
    // Set some constants to use to calculate the number of hours,
    // minutes, etc.
#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR (SECONDS_PER_MINUTE * 60)

    // Get the number of hours in the elapsed time by dividing by
    // SECONDS_PER_HOUR and rounding down.
    int hours = (time / SECONDS_PER_HOUR);

    // Subtract the number of hours (in seconds) from the timestamp.
    time -= (hours * SECONDS_PER_HOUR);

    // Get the number of minutes in the elapsed time by dividing by
    // SECONDS_PER_MINUTE and rounding down.
    int minutes = (time / SECONDS_PER_MINUTE);

    // Subtract the number of minutes (in seconds) from the timestamp.
    time -= (minutes * SECONDS_PER_MINUTE);

    // Allocate 17 char spaces (00:00:00.000000), which is 16, plus a null
    // terminator.
    char* timeString = cautiousMalloc(17);

    // Fill the timeString buffer with the result of sprintf, using the
    // %02d format specifier (2 digit number, filling with zeroes) and the
    // float specifier, for the seconds.
    snprintf(timeString, 13, "%02d:%02d:%f", hours, minutes, time);

    // Return the timeString.
    return timeString;
}

void runBogoSort(int numberOfItemsInList) {
    // Set the seed of the random number generator.
    srand((unsigned int)time(NULL));

    // Grab an array of random items.
    int* array = randomArrayOfLength(numberOfItemsInList);

    // Print that array.
    printArray(array, numberOfItemsInList);

    // Grab the clock right before iterating.
    clock_t start = clock();

    // Grab the numberOfIterations returned by BogoSorting the
    // array.
    long long unsigned int numberOfIterations = bogoSort(array,
                                                         numberOfItemsInList
                                                         );

    // Once we've done that, grab the clock at the end.
    clock_t end = clock();

    // Print the array again, once we're done.
    printArray(array, numberOfItemsInList);

    // Grab the elapsed time by casting the difference of the
    // two CPU clocks to a double and dividing by CLOCKS_PER_SEC,
    // a macro in time.h.
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Grab the formatted time from that elapsed time using the
    // formattedTime method.
    char* timeString = formattedTimeFromDouble(elapsed);

    // Print the time it took for the sort. Use that timeString we made
    // earlier.
    printf("It took me %s to BogoSort this list.\n", timeString);

    // Set the locale to LC_NUMERIC so we can use the ' flag in our format.
    setlocale(LC_NUMERIC, "");

    // Create a string that says 'times' or 'time' depending whether or not there
    // was only one iteration.
    char* numberOfTimesString = numberOfIterations == 1 ? "time" : "times";

    // Print the number of times, formatted with thousands separators
    // (thanks, locale.h.)
    printf("I shuffled it %'llu %s.\n", numberOfIterations, numberOfTimesString);

    // Free the timeString.
    free(timeString);

    // Free the array.
    free(array);
}
