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


// function prototypes
//void readCityData(string fileName, int* citiesX, int* citiesY, int &N);
//void genAdjMatrix(int ** matrix, int N, int* citiesX, int* citiesY);



int main(int argc, char** argv){

	//command line arg error check
	if (argc != 2)
	{
		cout << "Please enter file name for processing." << endl;
		return 1;
	}


	//set seed for RNG
	unsigned seed = time(nullptr);
	srand(seed);

	//create arrays for holding city coordinates
    int citiesX[16000];
    int citiesY[16000];
    int N = 0; //number of cities


	// Get filename from command line and read data from file	
	string fileName = argv[1];
    readCityData(fileName, citiesX, citiesY, N);

	if (N > 0) //ensure that file exists
	{
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


		//create array for holding numTours hamiltonian tours
		//each tour is based off of an MST with diff starting vertices
		int numTours = 5;
		int** ham = new int*[numTours];

		for (int i = 0; i < numTours; i++)
		{
			ham[i] = new int[N + 1];
		}

		//generate numTour hamiltonian tours, apply 1x psuedo-2opt
		//(each tour is based off of an MST with diff starting vertex)
		//and take the shortest for further optimization

		int bestTour = 0;
		int bestTourLength = 999999999; //infinity
		for (int tour = 0; tour < numTours; tour++)
		{

			//create dynamic array of pointers to linked lists for adjacency list (mst)
			struct LinkedList** mst = new LinkedList*[N];
			for (int row = 0; row < N; row++)
			{
				//each row represents a vertex and its adjacencies
				mst[row] = linkedListCreate();
			}

			//create vector for holder euler tour
			vector<int> euler;

			//gen random starting city
			int firstVert = rand() % (N - 0 + 1) + 0;
			//cout << "First Vert: " << firstVert << endl << endl;//TEST

			//create MST
			primMST(matrix, N, mst, firstVert);

			////TEST: print adjacency list
			//for (int i = 0; i < N; i++)
			//{
			//	cout << i << " -> ";
			//	linkedListPrint(mst[i]);
			//	cout << endl;
			//}

			//find degree of each vertex in MST
			for (int row = 0; row < N; row++)
			{
				//each row represents a vertex and its adjacencies
				mstDegree[row] = linkedListGetSize(mst[row]);
				//cout << "City: " << row << " Degree: " << mstDegree[row] << endl;//TEST
			}

			//Find min-weight perfect matching and add to mst
			findMatching(matrix, mst, mstDegree, N);

			////TEST: print updated adjacency list (union of mst
			////and perfect matching
			//for (int i = 0; i < N; i++)
			//{
			//	cout << i << " -> ";
			//	linkedListPrint(mst[i]);
			//	cout << endl;
			//}

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
			hamTransform(euler, ham[tour], N);

			//TEST: print ham tour
			cout << endl;
			cout << "Ham tour: ";
			for (int i = 0; i <= N; i++)
			{
				cout << ham[tour][i] << " ";
			}


			//run pseudo two-opt on ham tour
			for (int i = 0; i < 1; i++)
			{
				pseudoTwoOpt(ham[tour], matrix, N);
			}

			//calculate tour length
			int tourLength = 0;
			for (int i = 0; i < N; i++) {
				tourLength += matrix[ham[tour][i]][ham[tour][i + 1]];
			}

			//determine best tour
			if (tourLength < bestTourLength)
			{
				bestTourLength = tourLength;
				bestTour = tour;
			}

			//delete allocated memory in mst
			for (int row = 0; row < N; row++)
			{
				linkedListDestroy(mst[row]);
			}
			delete[] mst;
			mst = nullptr;

			cout << endl << endl;

		} //end MST testing loop


		cout << "Start second round of k-opt" << endl << endl;


		//run k-opt on best ham tour
		for (int i = 0; i < 1; i++)
		{
			pseudoTwoOpt(ham[bestTour], matrix, N);
		}


		//calculate best tour length
		int tourLength = 0;
		for (int i = 0; i < N; i++) {
			tourLength += matrix[ham[bestTour][i]][ham[bestTour][i + 1]];
		}
		cout << endl << endl << "Best Tour Length = " << tourLength << endl << endl;//TEST


		//write data to output file
		string outputFile = argv[1];
		outputFile.append(".tour");
		writeTourData(outputFile, tourLength, ham[bestTour], N);



		//deallocate memory from matrix and arrays
		for (int i = 0; i < numTours; i++)
		{
			delete[] ham[i];
		}
		delete[] ham;
		ham = nullptr;

		for (int row = 0; row < N; row++)
		{
			delete[] matrix[row];
		}
		delete[] matrix;
		matrix = nullptr;
		delete[] mstDegree;
		mstDegree = nullptr;
		delete[] ham;
		ham = nullptr;
	}
    return 0;
}




