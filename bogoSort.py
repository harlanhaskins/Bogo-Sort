import random
import datetime

def swap(lst, i, j):
    temp = lst[i]
    lst[i] = lst[j]
    lst[j] = temp

def randomize(lst):
    for index in range(len(lst)):
        swap(lst, random.randint(0, len(lst) - 1), random.randint(0, len(lst) - 1))

def bogoSort(lst):
    ticks = datetime.datetime.now()
    totalIterations = 0
    while (not isSorted(lst)):
        #if totalIterations % (400 * len(lst)) == 0:
        print(lst)
        randomize(lst)
        totalIterations += 1
    endTicks = datetime.datetime.now()
    elapsedTime = endTicks - ticks
    print(lst)
    print("Total Number of Iterations is: " + str(totalIterations))
    print("Elapsed Time is: " + str(elapsedTime))

def isSorted(lst):
    for mark in range(len(lst) - 1):
        if lst[mark] > lst[mark + 1]:
            return False
    return True

def randomListWithNumberOfObjects(n):
    lst = []
    for number in range(n):
        lst += [random.randint(0, 100)]
    return lst

numberOfItems = int(input("How many items would you like in your list? "))
bogoSort(randomListWithNumberOfObjects(numberOfItems))
