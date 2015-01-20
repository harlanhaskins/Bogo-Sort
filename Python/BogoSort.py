import random
import datetime

def bogoSort(lst):
    # Initialize a totalIterations variable.
    totalIterations = 0

    # Run the commands below while the list isn't sorted.
    while (not isSorted(lst)):
        # Shuffle the list.
        random.shuffle(lst)

        # Add to total iterations.
        totalIterations += 1

    # Return the total iterations.
    return totalIterations

def isSorted(lst):
     # Iterate through the list.
    for mark in range(len(lst) - 1):

        # If at any point the current number is bigger than the one
        # in front of it, return false. It's not sorted.
        if lst[mark] > lst[mark + 1]:
            return False

    # If it iterated properly, return True.
    return True

def randomListWithNumberOfObjects(n):
    # Create a blank list object.
    lst = []

    # Iterate to the number and add random integer (1 - 100)
    for number in range(n):
        lst.append(random.randint(0, 10 * n))

    # Return that new list.
    return lst

def runBogoSort():
    # Prompt the user for a number of items for the list.
    number = input("How many items would you like in your list? ")

    # Cast that to an int.
    numberOfItems = int(number)

    # Create a randomized list.
    lst = randomListWithNumberOfObjects(numberOfItems)

    # Print the list for comparison's sake.
    print(lst)

    # Start the timer. Essentially create a reference to now.
    ticks = datetime.datetime.now()

    # Run the bogoSort! Save the return value as the number of Iterations.
    totalIterations = bogoSort(lst)

    # Get the finished-sorting time.
    endTicks = datetime.datetime.now()

    # Compare that to the starting time to find an elapsed time.
    elapsedTime = endTicks - ticks

    # Print the sorted list.
    print(lst)

    # Print the elapsed time.
    print("It took me " + str(elapsedTime) + " to BogoSort this list.")

    # Create a string for the word 'time'.
    timeString = 'time'

    # Add an 's' to the end if the number of iterations is anything but 1.
    if not (totalIterations == 1):
        timeString += 's'

    # Add grouping separators to numbers using Python string formats.
    formattedIterations = '{:,}'.format(totalIterations)

    # Print the number of iterations.
    print("I shuffled it " + formattedIterations + " " + timeString + ".")

    # If the list was not sorted from the beginning.
    if totalIterations > 0:

        # Calculate the speed.
        speed = totalIterations / elapsedTime.total_seconds()

        # Format it to have only two fractional digits.
        formattedSpeed = '{:.2f}'.format(speed)

        # Print the speed.
        print("I checked " + formattedSpeed + " permutations per second.")
