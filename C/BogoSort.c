// For printf() and sprintf().
#include <stdio.h>

// For srandom and random
#include <stdlib.h>

// For clock() and the clock_t type.
#include <time.h>

// For setLocale() and the ' format flag.
#include <locale.h>

// For boolean variables.
#include <stdbool.h>

void swap(int *array, int firstIndex, int secondIndex) {
    // Create a temp variable to store the first index, because we'll
    // be overwriting it.
    int temp = array[firstIndex];

    // Set the value at the first index to the value at the second index.
    array[firstIndex] = array[secondIndex];

    // Set the value at the second index to the value of the first index.
    array[secondIndex] = temp;
}

bool isSorted(int* array, size_t length, bool ascending) {
    // Iterate through the array.
    for (size_t i = 1; i < length; i++) {
        // If at any point the previous array item is greater than (or
        // less than, in the case of descending arrays, return false. 
        if ((array[i - 1] > array[i]) == ascending) {
            return false;
        }
    }
    // If the for loop exited successfully, return true.
    return true;
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
            swap(array, 0, 1);
            return;
        }
        // Reset the first index to some random number.
        firstIndex = random() % length;

        // This while loop handles the unlikely circumstance of both
        // numbers being entirely equal.
        while (secondIndex == firstIndex) {
            // Reset the second index to a random number.
            secondIndex = random() % length;
        }
        // Run the swap function with the two random indices.
        swap(array, firstIndex, secondIndex);
    }
}

void printArray(int* array, size_t length) {
    // Print a bracket (for pretty printing.)
    putchar('[');

    // Iterate through the numbers in the array.
    for (size_t i = 0; i < length; i++) {
        // Print the number at the current index
        printf("%d", array[i]);

        // If the number is not the last number in the array...
        if (i != length - 1) {
            // ...then print a comma and a space after it.
            fputs(", ", stdout);
        }
    }
    // Print the closing bracket and the newline character.
    putchar(']');
    putchar('\n');
}

int* randomArrayOfLength(size_t length) {
    // Allocate an array of the length specified.
    int *array = malloc(length * sizeof(int));

    // Iterate (length) times.
    for (size_t i = 0; i < length; i++) {
        // Add a random number from 0 to (length * 3).
        array[i] = random() % (length * 3);
    }

    // Return the random array.
    return array;
}

long long unsigned int bogoSort(int* array, size_t length) {
    // Initialize a number of iterations.
    long long unsigned int iteration = 0;

    // Run a loop while the array is not sorted. This is an O(n) operation
    // running multiple millions of times. Deal with it.
    while (!isSorted(array, length, true)) {
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
    const int SECONDS_PER_MINUTE = 60;
    const int SECONDS_PER_HOUR = SECONDS_PER_MINUTE * 60;
    
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
    
    // Allocate 13 char spaces (00:00:00.000), which is 12, plus a null
    // terminator.
    char* timeString = malloc(13); 

    // Fill the timeString buffer with the result of sprintf, using the
    // %02d format specifier (2 digit number, filling with zeroes) and the
    // float specifier, for the seconds.
    sprintf(timeString, "%02d:%02d:%f", hours, minutes, time);

    // Return the timeString.
    return timeString;
}

int main(){
    
    // Set the seed of the random number generator.
    srandom(time(0));
    
    // Declare the number of variables.    
    size_t numberOfItemsInList;
    
    // Print a question for the user.
    fputs("How many items would you like in your list? ", stdout);
    
    // Scan user input and fill the buffer we declared.
    scanf("%zu", &numberOfItemsInList);

    // Grab an array of random items.
    int* array = randomArrayOfLength(numberOfItemsInList); 
        
    // Print that array.
    printArray(array, numberOfItemsInList);

    // Grab the clock right before iterating.
    clock_t start = clock();
    
    // Grab the numberOfIterations returned by BogoSorting the 
    // array.
    long long unsigned int numberOfIterations = bogoSort(array,
                                                         numberOfItemsInList);
    
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

