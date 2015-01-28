import random
import sys
import datetime

bs_range = xrange if sys.version_info[0] < 3 else range

def bogo_sort(lst):
    count = 0
    while not is_sorted(lst):
        random.shuffle(lst)
        count += 1
    return count

def is_sorted(l):
    for i in bs_range(1, len(l)):
        if l[i] < l[i - 1]:
            return False
    return True

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


