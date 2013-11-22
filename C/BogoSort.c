#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

typedef int bool;
#define true 1
#define false 0

void swap(int *array, int firstIndex, int secondIndex) {
    int temp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = temp;
}

bool isSorted(int* array, int length) {
    for (int i = 1; i < length; i++) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}

void shuffleArray(int* array, int length) {
    int firstIndex = 0;
    int secondIndex = 0;
    for (int i = 0; i < length; i++) {
        firstIndex = arc4random_uniform(length);
        while (secondIndex -= firstIndex) {
            secondIndex = arc4random_uniform(length);
        }
        swap(array, firstIndex, secondIndex);
    }
}

void printArray(int* array, int length) {
    printf("[");
    for(int i = 0; i < length; i++) {
        printf("%d", array[i]);
        if (i != length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int* randomArrayOfLength(int length) {
    int *array = malloc(length * sizeof(int));
    for(int i = 0; i < length; i++) {
        array[i] = arc4random_uniform(length * 3);
    }
    return array;
}

int bogoSort(int* array, int length) {
    int iteration = 0;
    while (!isSorted(array, length)) {
        shuffleArray(array, length);
        iteration++;
    }
    return iteration;
}

char* formattedTimeFromDouble(double time) {
    int hours = floor(time / 3600);
    time -= (hours * 3600);
    int minutes = floor(time / 60);
    time -= (minutes * 60);
    
    char* timeString = malloc(13 * sizeof(char));

    sprintf(timeString, "%02d:%02d:%f", hours, minutes, time);

    return timeString;
}

int main(int argc, char *argv[]) {
    
    int numberOfItemsInList;
    
    printf("How many items would you like in your list? ");
    
    scanf("%d", &numberOfItemsInList);

    int* array = randomArrayOfLength(numberOfItemsInList); 
        
    printArray(array, numberOfItemsInList);

    clock_t start = clock();
    
    int numberOfIterations = bogoSort(array, numberOfItemsInList);
    
    clock_t end = clock();
    
    printArray(array, numberOfItemsInList);
    
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    char* timeString = formattedTimeFromDouble(elapsed);
    
    printf("It took me %s to BogoSort this list.\n", timeString);
    
    setlocale(LC_NUMERIC, "");
    
    printf("I shuffled it %'d times.\n", numberOfIterations);
    
    free(timeString);

    free(array);
}

