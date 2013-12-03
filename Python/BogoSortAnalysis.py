from BogoSort import *
import os
import errno

def runAnalysis():
    endingLength = int(input("Up to how many items would you like to test? "))
    numberOfTrials = int(input("How many trils would you like to run? "))
    
    directory = "./BogoSortResults"
    createPath(directory)
    fileName = directory + "/PythonBogoSort_" + str(numberOfTrials) + "-trials_" + str(endingLength) + "-items_" + datetime.datetime.now().strftime("%Y%m%dT%I%M%S%p") + ".csv"
    
    outputFile = open(fileName, "w+")

    print("Length,Trial,Elapsed Time,Number of Shuffles", file=outputFile)
    
    for length in range(1, endingLength + 1):
        for trial in range(1, numberOfTrials + 1):
            # Create a randomized list.
            lst = randomListWithNumberOfObjects(length)
            
            # Start the timer. Essentially create a reference to now.
            ticks = datetime.datetime.now()

            # Run the bogoSort! Save the return value as the number of Iterations.
            totalIterations = bogoSort(lst)
            
            # Get the finished-sorting time.
            endTicks = datetime.datetime.now()

            # Compare that to the starting time to find an elapsed time.
            elapsedTime = (endTicks - ticks)
            printString = "%d,%d,%f,%d" % (length, trial, elapsedTime.seconds, totalIterations)
            print(printString, file=outputFile)

def createPath(path):
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise            
