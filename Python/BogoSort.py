import random
import datetime


def bogo_sort(lst):
    count = 0
    while not sorted(lst):
        random.shuffle(lst)
        count += 1
    return count


def random_list(length):
    return [random.randint(0, 10 * length) for _ in range(length)]


def run_bogo_sort(length):
    lst = random_list(length)
    print(lst)

    start = datetime.datetime.now()
    iterations = bogo_sort(lst)
    end = datetime.datetime.now()

    elapsed = end - start
    return lst, iterations, elapsed


def print_results(lst, iterations, elapsed):
    print(lst)
    print("It took me " + str() + " to BogoSort this list.")

    # Add grouping separators to numbers using Python string formats.
    formatted_iterations = '{:,}'.format(iterations)

    time_string = 'time' if iterations == 1 else 'times'

    print("I shuffled it " + formatted_iterations + " " + time_string + ".")

    if iterations > 0:
        speed = iterations / elapsed.total_seconds()
        formatted_speed = '{:.2f}'.format(speed)
        print("I checked " + formatted_speed + " permutations per second.")
