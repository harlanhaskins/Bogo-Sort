import random
import datetime

def swap(lst, i, j):
    lst[i] , last[j] = lst[j] , lst[i]

def randomize(lst):
    for index in range(len(lst)):
        swap(lst, random.randint(0, len(lst) - 1),
            random.randint(0, len(lst) - 1))

def bogoSort(lst):
    print(lst)
    ticks = datetime.datetime.now()
    totalIterations = 0
    while (not isSorted(lst)):
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
