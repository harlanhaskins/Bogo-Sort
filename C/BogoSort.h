/* This is a header that publicly exposes some BogoSort methods.
 */

// For printf() and sprintf().
#include <stdio.h>

// For srandom and random
#include <stdlib.h>

// For clock() and the clock_t type.
#include <time.h>

// For setLocale() and the ' format flag.
#include <locale.h>

int* randomArrayOfLength(size_t length);

void printArray(int* array, size_t length);

void swap(int* array, int firstIndex, int secondIndex);

unsigned int isSorted(int* array, size_t length);

void shuffleArray(int* array, size_t length);

long long unsigned int bogoSort(int* array, size_t length);

char* formattedTimeFromDouble(double elapsedTime);
