//---------------------------------------------------------------------------
//	CS 325 - Group Project - Traveling Salesman Problem
//
//
//
//
//
//----------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include "christofides.hpp"
#include "twoOpt.hpp"
#include "utilities.hpp"
#include "threeOpt.hpp"


using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;



int main(){

    int citiesX[16000];
    int citiesY[16000];
    int N = 0;
    int tourLength = 0;

	// Testing with hardcoded file name
    string fileName = "./test-input-1.txt"; // for testing, revise for CL input
    readCityData(fileName, citiesX, citiesY, N);
    if(N > 0){

	//create dynamic 2D array for adj matrix
	int** matrix = new int*[N];
	for (int row = 0; row < N; row++)
	{
		matrix[row] = new int[N];
	}

	//create adjacency matrix
	genAdjMatrix(matrix, N, citiesX, citiesY);

	//create array for holding Degree of each vertex in mst
	int* mstDegree = new int[N];

	//create vector for holder euler tour
	vector<int> euler;

	//create array for holding hamiltonian tour
	int* ham = new int[N+1];

	//create dynamic array of pointers to linked lists for adjacency list (mst)
	struct LinkedList** mst = new LinkedList*[N];
	for (int row = 0; row < N; row++)
	{
		//each row represents a vertex and its adjacencies
		mst[row] = linkedListCreate();
	}


	//create MST
	primMST(matrix, N, mst);

	//TEST: print adjacency list
	for (int i = 0; i < N; i++)
	{
		cout << i << " -> ";
		linkedListPrint(mst[i]);
		cout << endl;
	}

	//find degree of each vertex in MST
	for (int row = 0; row < N; row++)
	{
		//each row represents a vertex and its adjacencies
		mstDegree[row] = linkedListGetSize(mst[row]);
		cout << "City: " << row << " Degree: " << mstDegree[row] << endl;//TEST
	}

	//Find min-weight perfect matching and add to mst
	findMatching(matrix, mst, mstDegree, N);

	//TEST: print updated adjacency list (union of mst
	//and perfect matching
	for (int i = 0; i < N; i++)
	{
		cout << i << " -> ";
		linkedListPrint(mst[i]);
		cout << endl;
	}

	//create Eulier circuit tour of modified mst
	findEuler(euler, mst);

	//TEST: print euler tour
	int vectSize = euler.size();
	cout << "Euler tour: ";
	for (int i = 0; i < vectSize; i++)
	{
		cout << euler[i] << " ";
	}

	//transform euler circuit into ham cycle
	hamTransform(euler, ham, N);

	//TEST: print ham tour
	cout << endl;
	cout << "Ham tour: ";
	for (int i = 0; i <= N; i++)
	{
		cout << ham[i] << " ";
	}


	//run two-opt on ham tour
	for(int i = 0; i < 3; i++)
	{
		tourLength = pseudoTwoOpt(ham, matrix, N);
	}

	// --- Run Full version of 2-Opt
        tourLength = twoOpt(ham, matrix, N);
        cout << endl << endl << "Tour Length from twoOpt = " << tourLength << endl << endl;

        // --- Run Pseudo-3-Opt
         tourLength = KOpt(ham, matrix, N);
         tourLength = KOpt(ham, matrix, N);
      //  tourLength = pseudoTwoOpt(ham, matrix, N);
      //  tourLength = threeOpt(ham, matrix, N);
      //  tourLength = pseudoTwoOpt(ham, matrix, N);
      //  tourLength = threeOpt(ham, matrix, N);


	//TEST: print tour length
	tourLength = 0;
	for (int i = 0; i < N; i++) {
		tourLength += matrix[ham[i]][ham[i + 1]];
	}
	cout << endl << endl << "Tour Length = " << tourLength << endl << endl;


// --- Write Tour Result in Project Required Format
       writeFinalTour(fileName, ham, N, tourLength);

// --- Write Tour with Coordinates included for Plotting in Excel
       writeTourWithCoords(fileName, ham, N, tourLength, citiesX, citiesY);



	//deallocate memory from matrix and arrays
	for (int row = 0; row < N; row ++)
	{
		delete[] matrix[row];
		linkedListDestroy(mst[row]);
	}
	delete[] matrix;
	matrix = nullptr;
	delete[] mst;
	mst = nullptr;
	delete[] mstDegree;
	mstDegree = nullptr;
	delete[] ham;
	ham = nullptr;

    } // end if N > 0
    return 0;
}



