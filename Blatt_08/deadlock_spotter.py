#!/usr/bin/python3

import numpy as np
from Input import In

print("\nNumber of Processes: {}".format(In["NP"]))
print("Number of Resources: {}".format(In["NR"]))
print("E: {}".format(In["E"]))
print("C: {}".format(In["C"]))
print("R: {}\n".format(In["R"]))

deadlock = False

print("Creating Resource rest vector A...")

A = In["E"]

for i in range(len(In["E"])):
    for ii in range(len(In["C"])):
        A[i]-=In["C"][ii][i]

print("A: {}".format(A))

############################### Start algorithm ##############################

# After every step: print Index of process and A
print("PI: ...")
print("Vector A:")

# Print all Process indices if there is a deadlock
if deadlock: print("All PI:")



