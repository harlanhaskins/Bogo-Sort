from __future__ import print_function
from bogosort import *
import os
import errno

def create_path(path):
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise

def run_analysis(ending_length, number_of_trials):
    
    directory = "./BogoSortResults"
    create_path(directory)
    file_name = ("{dir}/BogoSort_{n}-trials_{i}-items_{date}.csv"
        .format(dir=directory, n=number_of_trials, i=ending_length,
                date=datetime.datetime.now().strftime("%Y%m%dT%I%M%S%p")))

    with open(file_name, "w+") as output_file:

        print("Length,Trial,Elapsed Time,Number of Shuffles", file=output_file)

        for length in range(1, ending_length + 1):
            for trial in range(1, number_of_trials + 1):
                lst, iterations, elapsed = run_bogo_sort(length)

                print_string = "%d,%d,%f,%d" % (length, trial,
                                                elapsed.seconds, iterations)
                print(print_string, file=output_file)
