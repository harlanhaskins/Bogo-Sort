import random
import datetime

def swap(lst, i, j):
    # Use Python tuble-swap to swap two list elements.
    lst[i] , lst[j] = lst[j] , lst[i]

def randomize(lst):
    # Iterate through the list and swap the item at the current index
    # with a random index
    for index in range(len(lst)):
        swap(lst, index, random.randint(0, len(lst) - 1))

def bogoSort(lst):
    # Initialize a totalIterations variable.
    totalIterations = 0

    # Run the commands below while the list isn't sorted.
    while (not isSorted(lst)):
        # Shuffle the list.
        randomize(lst)

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
        lst += [random.randint(0, 3 * n)]
    
    # Return that new list.
    return lst

def main():
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

# Call the main function.
main()
