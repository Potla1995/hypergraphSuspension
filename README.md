# Hypergraph Suspension of Even Cycles: Comparison between D(11,3) and D'(11,3)

## Introduction

This is a repository containing code that verifies that the graphs D(3,11) and D'(3,11) are not isomorphic, as an addendum to [this paper](https://homepages.math.uic.edu/~potla/papers/hypergraphSuspension.pdf).

This "manual" is written to be reproduced in UNIX systems.
The equivalent steps can also be carried out on windows systems with the required software.


## Details of the verification

The file `exportAdjLists.cpp` contains code that generates the adjacency lists of the graphs `D(11,3)` and `D'(11,3)`.
These lists are generated and exported into csv files with the following convention: vertices in the left partition are labelled with {0,1,2}-strings of length 11, vertices in the right partition are labelled with {0,1,2}-strings of length 11 followed by a `'`.
The three neighbors of the first element in each line of the .csv file are included in the line after it.

After reading in these csv files into gephi, edges in the connected component of 00...0 of D(11,3) and D'(11,3) are filtered out, and the file `conn_comp_edges.py` is created containing these edges as lists.

The file `adjListToDiam.sage` contains code that reads in the `conn_comp_edges.py` file, generates the graphs CD(11,3) and CD'(11,3), and computes their diameters as well as the number of cycles through the edge {00...0, 00...0'}.

As D(11,3) is known to be edge-transitive, the number of cycles through any edge should be constant, and this should equal the number of cycles through the edge {00...0, 00...0'} lest they be isomorphic.
However, we find 112 such cycles in D(11,3) but only 4 such cycles in D'(11,3).

## Requirements for running the code

The following programs are required to run this code: `g++`, `python3`, `gephi`, `sagemath`.

The result takes approximately 6 hours of computation time on an AMD Ryzen 5 3600 processor running at 3.97GHz.


## Instructions for reproducing the result

+ Step 1: Compile and run `exportAdjLists.cpp` via
```
g++ exportAdjLists.cpp | ./a.out
```
+ Step 3: Use `gephi` to filter the connected components of 00...0, and output the filtered edges to two .csv files.
Format the exported csv files into a `conn_comp_edges.py` file containing lists of the edges in the connected components.

+ Step 2: Run
```
sage adjListToDiam.sage
```

## Output
The following is the console output from Step 2.
```bash
Component sizes for D(11,3) and D'(11,3):
[39366, 39366, 39366, 39366, 39366, 39366, 39366, 39366, 39366]
[39366, 39366, 39366, 39366, 39366, 39366, 39366, 39366, 39366]

Diameter of D(11,3): 22, Diameter of D'(11,3): 20

Number of paths from 0 (left) to 0 (right):
in D(11,3): 113, in D'(11,3): 5
```

The file `Cycles_through_00.txt` contains the list of cycles in D(11,3) and D'(11,3) through the edge {00...0, 00...0'} (the program counts the edge itself as a cycle of length 2).

## Conclusion
The above proves that the graphs D(11,3) and D'(11,3) are not isomorphic. 