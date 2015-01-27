from bogosort import *
from bogosortanalysis import *
import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--size", help="The number of items to sort.",
                        type=int)
    parser.add_argument("-s", "--single-sort", help="Only sort one list.",
                        action="store_true")
    parser.add_argument("-t", "--trials", help="How many trials to analyze",
                        type=int, default=0)
    parser.add_argument("-b", "--beginning-length", help="How many items"+ 
                        " to start the sorting.", type=int, default=0)

    args = parser.parse_args()

    if not args.single_sort ^ args.trials:
        parser.print_help()
        exit(1)

    if args.single_sort:
        lst, iterations, elapsed = run_bogo_sort(args.size)
        print_results(lst, iterations, elapsed)
    else:
        run_analysis(args.beginning_length, args.size, args.trials)

def print_results(lst, iterations, elapsed):
    print(lst)
    print("It took me " + str(elapsed) + " to BogoSort this list.")

    # Add grouping separators to numbers using Python string formats.
    formatted_iterations = '{:,}'.format(iterations)

    time_string = 'time' if iterations == 1 else 'times'

    print("I shuffled it " + formatted_iterations + " " + time_string + ".")

    if iterations > 0:
        speed = iterations / elapsed.total_seconds()
        formatted_speed = '{:.2f}'.format(speed)
        print("That's " + formatted_speed + " shuffles per second.")

if __name__ == "__main__":
    main()

