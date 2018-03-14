//---------------------------------------------------------------------------
//	CS 325 - Utility Functions for the TSP Project
//----------------------------------------------------------------------------

#include "utilities.hpp"

#include <string>
#include <cstdlib>
#include <cmath>

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::string;



// -------------------------------------------------------------------
// --- Function readCityData
// --- Reads Data from a file formatted for the TSP Project
// --------------------------------------------------------------------
void readCityData(string fileName, int* citiesX, int* citiesY, int &N) {

	int ID;

	std::ifstream inFile;
	inFile.open(fileName.c_str());

	if (inFile.fail()) {
		cout << endl << "File could not be opened for reading.\n";
		cout << endl;
	}
	else {
		while (inFile >> ID) {
			inFile >> citiesX[ID];
			inFile >> citiesY[ID];
		}
		N = ID + 1;
	}
	inFile.close();

	return;
}


// -------------------------------------------------------------------
// --- Function writeFinalTour
// --- Writes the resulting tour to a text file
// --- appending the inFileName with the extension ".tour"
// --- First line written is the tour Length, followed by the city ID's
// --- In the order of the tour
// --------------------------------------------------------------------
void writeFinalTour(string fileName, int* tour, int N, int tourLength) {

	std::ofstream outFile;
	fileName = fileName + ".tour";
	outFile.open(fileName.c_str());

	if (outFile.fail()) {
		cout << endl << "File could not be opened for writing.\n";
		cout << endl;
	}
	else {
		outFile << tourLength << endl;
		for (int i = 0; i < N; i++) {
			outFile << tour[i] << endl;
		}
	}
	outFile.close();
	return;
}


// -------------------------------------------------------------------
// --- Function genAdjMatrix
// --- Takes in pointers to an empty matrix and city coordinate arrays
// --- Calculates Distances between cities, and fills the matrix
// --------------------------------------------------------------------
void genAdjMatrix(int ** matrix, int N, int* citiesX, int* citiesY)
{
	int colStart = 0;

	//calculate distance from a given city (row index) to every other city (col index)
	for (int row = 0; row < N; row++)
	{

		for (int col = colStart; col < N; col++)
		{
			//calculate distance between cities (row index and col index)
			double distance = sqrt(pow((citiesX[row] - citiesX[col]), 2) +
				pow((citiesY[row] - citiesY[col]), 2));

			//insert distance in both cells in matrix that correspond to edge
			matrix[row][col] = round(distance);
			matrix[col][row] = round(distance);

		}

		//can start 1 col later because prev col has already been filled in
		colStart++;

	}
	return;
}


// -------------------------------------------------------------------
// --- Function writeTourWithCoords
// --- Writes the resulting tour to a text file
// --- appending the inFileName with the extension ".xy"
// --- First line written is the tour Length, followed by the city ID's
// --- and their coordinates. In the order of the tour
// --- NOTE:  This version includes the first city twice, to close the tour for Excel Plotting
// --------------------------------------------------------------------
void writeTourWithCoords(string fileName, int* tour, int N, int tourLength, int* citiesX, int* citiesY) {

	std::ofstream outFile;
	fileName = fileName + ".xy";
	outFile.open(fileName.c_str());

	if (outFile.fail()) {
		cout << endl << "File could not be opened for writing.\n";
		cout << endl;
	}
	else {
		outFile << tourLength << endl;
		for (int i = 0; i < N; i++) {
			outFile << tour[i] << ", " << citiesX[tour[i]] << ", " << citiesY[tour[i]] << endl;
		}  // write the first city again to close the circuit for plotting
		outFile << tour[0] << ", " << citiesX[tour[0]] << ", " << citiesY[tour[0]] << endl;
	}
	outFile.close();
	return;
}

// -------------------------------------------------------------------
// --- Function writeTourData
// -------------------------------------------------------------------
void writeTourData(string fileName, int tourLength, int* tour, int N)
{
	//open output file and read in data
	std::ofstream outFile;
	outFile.open(fileName);

	//write tour length to file
	outFile << tourLength << endl;

	//write city tour to file
	for(int i = 1; i < N; i++)
	{
		outFile << tour[i] << endl;
	}

	outFile.close();

}