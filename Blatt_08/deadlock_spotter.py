#!/usr/bin/python3

import numpy as np
import sys
from Input2 import In

print("#################### Program starts ####################")
print("\nNumber of Processes: {}".format(In["NP"]))
print("Number of Resources: {}".format(In["NR"]))
print("E: {}".format(In["E"]))
print("C: {}".format(In["C"]))
print("R: {}\n".format(In["R"]))

# Some error checking
if (In["NR"] != len(In["E"])):
    print("Error! Number of Resources in E ({}) does not match with number of Resources in NR ({})!".format(len(In["E"]),In["NR"]))
    sys.exit(1)
if (In["NP"] != len(In["C"])):
    print("Error! Number of Processes in C ({}) does not match with number of Processes in NP ({})!".format(len(In["C"]),In["NP"]))
    sys.exit(1)
elif (In["NP"] != len(In["R"])):
    print("Error! Number of Processes in R ({}) does not match with number of Processes in NP ({})!".format(len(In["R"]),In["NP"]))
    sys.exit(1)

print("Creating Resource rest vector A...")

A = In["E"]

for i in range(In["NR"]):
    for ii in range(In["NP"]):
        A[i]-=In["C"][ii][i]

print("A: {}".format(A))

############################### Start algorithm ##############################
deadlock = False

marked=[]

# First go through all processes and check if they need to be marked
print("\nFirst iteration starts...")
for i in range(In["NP"]):
    mark = True
    for ii in range(In["NR"]):
        if (In["R"][i][ii] > A[ii]):
            mark = False
    if (mark == True):
        for ii in range(In["NR"]):
            A[ii]+=In["C"][i][ii]
        print("Process {} has been marked".format(i))
        print("A: {}".format(A))
    marked.append(mark)

unmarked_processes = marked.count(False)

# Second, go through all processes again, until there are no unmarked processes left, or a deadlock is found

print("\nStarting deadlock search...")
while not deadlock:
    previous_marks = marked.count(False)
    if (previous_marks == 0):
        print("No deadlocks found!")
        sys.exit(0)
    tmp = previous_marks
    for i in range(In["NP"]):
        mark = True
        if not (marked[i]):
            for ii in range(In["NR"]):
                if (In["R"][i][ii] > A[ii]):
                    mark = False
            if (mark == True):
                for ii in range(In["NR"]):
                    A[ii]+=In["C"][i][ii]
                print("Process {} has been marked".format(i))
                print("A: {}".format(A))
                marked[i] = True
                previous_marks-=1
    if (previous_marks == tmp):
        print("Deadlock found:")
        for i, mark in enumerate(marked):
            if not mark: print("Process {} takes part in a deadlock".format(i))
        deadlock = True
