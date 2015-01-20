from bogosort import *
from bogosortanalysis import *

def main():
    print("Welcome to BogoSort. Please enter the number of what you'd like to do.\n");
    print("\t1. Run a BogoSort");
    print("\t2. Save a series of BogoSorts");
    print("\t3. Quit");
    menuChoice = int(input("\nWhat would you like to do? "))

    choices = [exit, runBogoSort, runAnalysis, exit];

    choices[menuChoice]()

main()
