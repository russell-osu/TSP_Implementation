// --- Header file for the 3-Opt Algorithms

#ifndef TSP_3OPT_HPP
#define TSP_3OPT_HPP

#include "utilities.hpp"



// --------------------------------------------------------------------
// --- Function threeOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour with a three-opt approximation
// --------------------------------------------------------------------
int threeOpt(int* tour, int** matrix, int N);


// --------------------------------------------------------------------
// --- Function KOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour with a three-opt approximation
// --------------------------------------------------------------------
int KOpt(int* tour, int** matrix, int N);



// --------------------------------------------------------------------
// --- Function reversePath
// --- Takes in tour data, indexes of the tou
// --- Returns the tour with a two-Opt swap completed at those indexes
// --------------------------------------------------------------------
void reversePath(int* tour, int x, int y);


// --------------------------------------------------------------------
// --- Function findMinOpt
// --- Take in the tour, adjacency matrix and 3 nodes for 3-Opt consideration
// --- Compares change of length of each of 7 potential edge swaps
// --- and returns the Case that results in the greatest reduction (if any)
// --------------------------------------------------------------------
int findMinOpt(int* tour, int x, int y, int z, int** matrix, int &reduction);


// --------------------------------------------------------------------
// --- Function findMinOptK
// --- Take in the tour, adjacency matrix and 3 nodes for 3-Opt consideration
// --- Compares change of length of each of 7 potential edge swaps
// --- and returns the Case that results in the greatest reduction (if any)
// --------------------------------------------------------------------
int findMinOptK(int* tour, int x, int y, int z, int** matrix, int &reduction);



// --------------------------------------------------------------------
// --- Function splice
// --- Takes in tour data, indexes of the tour
// --- Starts with the x-y-path before the y-z-path and is
// --- changed so that the old x-y-path will follow the old y-z-path
// --------------------------------------------------------------------
void splice(int* tour, int x, int y, int z);




#endif

