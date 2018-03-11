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


using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;


// function prototypes
//void readCityData(string fileName, int* citiesX, int* citiesY, int &N);
//void genAdjMatrix(int ** matrix, int N, int* citiesX, int* citiesY);



int main(){

    int citiesX[16000];
    int citiesY[16000];
    int N = 0;

	// Testing with hardcoded file name	
    string fileName = "./tsp_example_1.txt"; // for testing, revise for CL input
    readCityData(fileName, citiesX, citiesY, N);


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
	twoOpt(ham, matrix, N);


	//TEST: print tour length
	int tourLength = 0;
	for (int i = 0; i < N; i++) {
		tourLength += matrix[ham[i]][ham[i + 1]];
	}
	cout << endl << endl << "Tour Length = " << tourLength << endl << endl;


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

    return 0;
}





///*--------------Functions Begin Here---------------*/
//
//
//// --- Reads Data from a file formatted for the TSP Project ----
//void readCityData(string fileName, int* citiesX, int* citiesY, int &N){
//
//    int ID;
//
//    std::ifstream inFile;
//    inFile.open(fileName.c_str());
//
//    if(inFile.fail()){
//	cout << endl << "File could not be opened for reading.\n";
//	cout << endl;
//    }
//    else{
//	while(inFile >> ID){
//	    inFile >> citiesX[ID];
//	    inFile >> citiesY[ID];
//	}
//	N = ID + 1;
//    }
//    inFile.close();
//
//    return;
//
//}
//
//
////generates adjacency matrix with city coordinate data 
//void genAdjMatrix(int ** matrix, int N, int* citiesX, int* citiesY)
//{
//	int colStart = 0;
//
//	//calculate distance from a given city (row index) to every other city (col index)
//	for(int row = 0; row < N; row++)
//	{
//		
//		for(int col = colStart; col < N; col++)
//		{
//			//calculate distance between cities (row index and col index)
//			double distance = sqrt(pow((citiesX[row] - citiesX[col]), 2) +
//			pow((citiesY[row] - citiesY[col]), 2));
//
//			//insert distance in both cells in matrix that correspond to edge
//			matrix[row][col] = static_cast<int>(round(distance));
//			matrix[col][row] = static_cast<int>(round(distance));
//			 
//		}
//
//		//can start 1 col later because prev col has already been filled in
//		colStart++;
//
//	}
//
//}


