// --- Header file for the general utilities used in the TSP program

#ifndef TSP_UTIL_HPP
#define TSP_UTIL_HPP

#include <string>
using std::string;

// -------------------------------------------------------------------
// --- Function readCityData
// --- Reads Data from a file formatted for the TSP Project
// --------------------------------------------------------------------
void readCityData(string fileName, int* citiesX, int* citiesY, int &N);


// -------------------------------------------------------------------
// --- Function writeFinalTour
// --- Writes the resulting tour to a text file
// --- appending the inFileName with the extension ".tour"
// --- First line written is the tour Length, followed by the city ID's
// --- In the order of the tour
// --------------------------------------------------------------------
void writeFinalTour(string inFileName, int* tour, int N, int tourLength);


// -------------------------------------------------------------------
// --- Function genAdjMatrix
// --- Takes in pointers to an empty matrix and city coordinate arrays
// --- Calculates Distances between cities, and fills the matrix
// --------------------------------------------------------------------
void genAdjMatrix(int ** matrix, int N, int* citiesX, int* citiesY);


// -------------------------------------------------------------------
// --- Function writeTourWithCoords
// --- Writes the resulting tour to a text file
// --- appending the inFileName with the extension ".tour"
// --- First line written is the tour Length, followed by the city ID's
// --- and their coordinates. In the order of the tour
// --------------------------------------------------------------------
void writeTourWithCoords(string fileName, int* tour, int N,
	int tourLength, int* citiesX, int* citiesY);


// -------------------------------------------------------------------
// --- Function cityDist
// -------------------------------------------------------------------
int cityDist(int** matrix, int row, int col);


#endif
