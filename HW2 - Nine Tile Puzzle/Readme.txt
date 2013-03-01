Name: Francesca Nannizzi
Student ID: 6330648898
Email Address: nannizzi@usc.edu
Date: 2.28.13

CSCI 460 - HW2: Nine Tile Puzzle

Question: Compare and comment on the performance observed when running A* with one heuristic 
versus the other. Briefly explain how they differ in execution. Which one is faster, 
Manhattan distance or misplaced tiles?

Using the Manhattan distance runs notably faster for a hard puzzle. The Manhattan distance works better because it takes into account tiles that are out of place, but also rates how out of place they are. Just using the number of misplaced tiles doesn't differentiate between a node that has tiles which are just barely out of place and one that has tiles which are completely out of place. 


1. The program structure is quite simple - a while loop for each heuristic calls functions to expand the current node, add the successors to the open list, move the current node to the closed list, and then choose a new current node. The Node class contains functions that perform operations directly on the node, and a struct for tile data.

2. To compile: g++ PuzzleSolver.cpp -o PS
   To execute: ./PS input.txt
   
3. 
