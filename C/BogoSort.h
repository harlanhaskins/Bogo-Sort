/* This is a header that publicly exposes some BogoSort methods.
 */

#ifndef BOGOSORT
#define BOGOSORT

// For printf() and sprintf().
#include <stdio.h>

// For srandom and random
#include <stdlib.h>

// For clock() and the clock_t type.
#include <time.h>

// For setLocale() and the ' format flag.
#include <locale.h>

extern int* randomArrayOfLength(size_t length);

extern void printArray(int* array, size_t length);

extern void printArrayToFile(int* array, size_t length, FILE* outputfile);

extern void swap(int* array, int firstIndex, int secondIndex, size_t length);

extern unsigned int isSorted(int* array, size_t length);

extern void shuffleArray(int* array, size_t length);

extern long long unsigned int bogoSort(int* array, size_t length, int verbose);

extern char* formattedTimeFromDouble(double elapsedTime);

extern int randonImtegerInRange(size_t min, size_t max);

extern void runBogoSort(int numberOfItemsInList, int verbose);

extern void* cautiousMalloc(size_t size);

#endif
