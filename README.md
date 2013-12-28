Bogo Sort
======

The greatest sorting algorithm known to man.

BogoSort follows a simple two-step process:

Step One: Check if the list is sorted. If it is, return. Otherwise...

Step Two: ...Shuffle the list and go back to step one!


Usage
======

    python3 main.py

or

    make; ./BogoSort

BogoSort will generate a list of the length you specify and sort it. Intelligently.

Sample Output
======
    
    ./BogoSort -s -n 13
    [27, 21, 35, 9, 12, 3, 6, 23, 25, 32, 35, 36, 37]
    [3, 6, 9, 12, 21, 23, 25, 27, 32, 35, 35, 36, 37]
    It took me 00:37:35.218139 to BogoSort this list.
    I shuffled it 9,185,663,135 times.
