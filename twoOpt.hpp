// --- Header file for the Two-Opt Algorithm

#ifndef TSP_TWOOPT_HPP
#define TSP_TWOOPT_HPP

#include "utilities.hpp"

// --------------------------------------------------------------------
// --- Function twoOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour with a full two-opt approximation
// --- Starts back at the beginning with every change (swap) of the tour
// --------------------------------------------------------------------
int twoOpt(int* tour, int** matrix, int N);


// --------------------------------------------------------------------
// --- Function pseudoTwoOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour using the general 2-Opt Method
// --- But does not return to the beginning when changes are made
// --- Continues from the current position Through the successively revised tour
// --------------------------------------------------------------------
int pseudoTwoOpt(int* tour, int** matrix, int N);


// --------------------------------------------------------------------
// --- Function swapEdges
// --- Takes in tour data, indexes of the tour
// --- Returns the tour with a two-Opt swap completed at those indexes
// --------------------------------------------------------------------
void swapEdges(int* tour, int x, int y);


// -------------------------------------------------------------------
// --- Function pathDiff
// --- Takes in tour data, indexes of the tour, and city coordinates,
// --- Returns the difference in length making a two-Opt swap would produce
// --------------------------------------------------------------------
int  pathDiff(int* tour, int j, int k, int** matrix);


// -------------------------------------------------------------------
// --- Function edgeLength
// --- Takes in tour data, indexes of the tour, and city coordinates,
// --- Returns distances between the cities
// --------------------------------------------------------------------
int edgeLength(int* tour, int j, int k, int** matrix);


#endif

