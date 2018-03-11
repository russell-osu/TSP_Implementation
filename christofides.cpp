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
#include "linkedList.hpp"
#include "dynArray.hpp"
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;


// function prototypes
void readCityData(string fileName, int* citiesX, int* citiesY, int &N);
void genAdjMatrix(int ** matrix, int N, int* citiesX, int* citiesY);
void primMST(int** matrix, int N, struct LinkedList ** mst);
void updateKey(int city, int newKey, DynArr* heap);
void findMatching(int **matrix, LinkedList** mst, int* mstDegree, int N);
void findEuler(vector<int> &euler, LinkedList** mst);
void hamTransform(vector<int> &euler, int* ham, int N);


int main(){

    int citiesX[16000];
    int citiesY[16000];
    //int tour[16000];
    int N = 0;
    //int i, j, k;
    //int reduction;

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

	//find degree of each vertex in MST
	for (int row = 0; row < N; row++)
	{
		//each row represents a vertex and its adjacencies
		mstDegree[row] = linkedListGetSize(mst[row]);
		cout << "City: " << row << " Degree: " << mstDegree[row] << endl;//TEST
	}

	//Find min-weight perfect matching and add to mst
	findMatching(matrix, mst, mstDegree, N);

	//create Eulier circuit tour of modified mst
	findEuler(euler, mst);

	//transform euler circuit into ham cycle
	hamTransform(euler, ham, N);

////print matrix for testing
//	for (int row = 0; row < N; row++)
//	{
//		for (int col = 0; col < N; col++)
//		{
//			cout << matrix[row][col] << " ";
//		}
//		cout << endl;
//	}

	//TEST -- print tour length
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




/*--------------Functions Begin Here---------------*/


// --- Reads Data from a file formatted for the TSP Project ----
void readCityData(string fileName, int* citiesX, int* citiesY, int &N){

    int ID;

    std::ifstream inFile;
    inFile.open(fileName.c_str());

    if(inFile.fail()){
	cout << endl << "File could not be opened for reading.\n";
	cout << endl;
    }
    else{
	while(inFile >> ID){
	    inFile >> citiesX[ID];
	    inFile >> citiesY[ID];
	}
	N = ID + 1;
    }
    inFile.close();

    return;

}


void genAdjMatrix(int ** matrix, int N, int* citiesX, int* citiesY)
{
	int colStart = 0;

	//calculate distance from a given city (row index) to every other city (col index)
	for(int row = 0; row < N; row++)
	{
		
		for(int col = colStart; col < N; col++)
		{
			//calculate distance between cities (row index and col index)
			double distance = sqrt(pow((citiesX[row] - citiesX[col]), 2) +
			pow((citiesY[row] - citiesY[col]), 2));

			//insert distance in both cells in matrix that correspond to edge
			matrix[row][col] = static_cast<int>(round(distance));
			matrix[col][row] = static_cast<int>(round(distance));
			 
		}

		//can start 1 col later because prev col has already been filled in
		colStart++;

	}

}


//build a minimum spanning tree from graph represented by matrix
void primMST(int** matrix, int N, struct LinkedList ** mst)
{
	//create min heap with city numbers and key 
	DynArr* vectHeap = newDynArr(N);
	//create key array (for easily retrieving key value)
	int* key = new int[N];
	//create array for tracking if vertex has been removed from heap
	int* inHeap = new int[N];
	//create array for tracking previous city
	int* prevCity = new int[N];
	prevCity[0] = -1; //first city has no previous city



	//add cities and key values to arrays (key set to infinity)
	//build heap by adding each vector to heap
	for (int city = 0; city < N; city++)
	{
		struct Vect temp;
		temp.cityNum = city;
		temp.key = 9999999; //infinity
		addHeap(vectHeap, temp);
		key[city] = 9999999;
		inHeap[city] = 1;
	}

	//first city/vector has key value of 0
	updateKey(0, 0, vectHeap);
	key[0] = 0;


	//build MST
	while(!isEmptyDynArr(vectHeap))
	{
		//get and remove city with lowest key weight from heap
		struct Vect u = getMinHeap(vectHeap);
		removeMinHeap(vectHeap); //remove from heap
		inHeap[u.cityNum] = 0; //remove from in-heap tracking array

		//search for vertices adjacent to u in matrix
		for(int v = 0; v < N; v++)
		{
			//get edge weight b/w v and u from adj matrix
			int edgeW = matrix[u.cityNum][v];
			//if v still in heap, (u,v) edge weight lower than key,
			//and u != v, add to MST
			if (inHeap[v] == 1 && edgeW < key[v] && edgeW > 0)
			{
				prevCity[v] = u.cityNum;
				key[v] = edgeW;
				//update key in min heap
				updateKey(v, edgeW, vectHeap);
			}
		}
	}

	
	//Add vertices to adjacency list
	for(int i = 1; i < N; i++)//skips first city;
	{
		linkedListAddBack(mst[prevCity[i]], i);
		linkedListAddBack(mst[i], prevCity[i]);
	}

	//TESTING: print adjacency list
	for(int i = 0; i < N; i++)
	{
		cout << i << " -> ";
		linkedListPrint(mst[i]);
		cout << endl;
	}

	//free all allocated memory
	deleteDynArr(vectHeap);
	delete[] key;
	key = nullptr;
	delete[] inHeap;
	inHeap = nullptr;
	delete[] prevCity;
	prevCity = nullptr;

}


//updates key value in min heap
void updateKey(int city, int newKey, DynArr* heap)
{
	int lastIndex = sizeDynArr(heap) - 1 ;

	//find index of node to update
	int currIndex = 0;
	while (city != heap->data[currIndex].cityNum)
	{
		currIndex++;
	}

	//create vect struct to replace old key value
	struct Vect temp;
	temp.cityNum = city;
	temp.key = newKey;

	//update key value at index found in search
	putDynArr(heap, currIndex, temp);

	//adjust heap to establish correct sort
	_adjustHeap(heap, lastIndex, currIndex);

}


//find a min-weight perfect matching of odd-parity 
//vertices in mst and add to mst
void findMatching(int **matrix, LinkedList** mst, int* mstDegree, int N)
{
	
	//create queue for holding odd parity vertices
	struct LinkedList *oddQ = linkedListCreate();

	//add odd-parity vertices to queue
	for(int i = 0; i < N; i++)
	{
		if(mstDegree[i] % 2 != 0)
		{
			linkedListAddBack(oddQ, i);
		}

	}
	 

	//loop through queue until empty, adding edges to MST
	while(!linkedListIsEmpty(oddQ))
	{
		//retrieve first item from queue
		int currVert = linkedListFront(oddQ);
		linkedListRemoveFront(oddQ);

		int dist = 9999999; //for distance calculation

		//find vertices in Q adj to current vertex
		//no need to search for all cities in Q
		//just check a city at front of Q, remove it from 
		//front of LL and add to back of LL, cycling through all cities in Q; 
		//when min dist veretex is 
		//found, just remove from linked list

		int qSize = linkedListGetSize(oddQ);


		int adjVert = 0;
		//loop through queue
		for(int i = 0; i < qSize; i++)
		{
			//remove adj v from front of queue
			int v = linkedListFront(oddQ);
			linkedListRemoveFront(oddQ);

			if (matrix[currVert][v] < dist)
			{
				dist = matrix[currVert][v];
				adjVert = v;
			}
			//re-add adj v to back of queue
			linkedListAddBack(oddQ, v);
		}

		//cout << currVert << " - " << adjVert << endl; //TEST

		//add edge to mst 
		linkedListAddBack(mst[currVert], adjVert);
		linkedListAddBack(mst[adjVert], currVert);

		//remove adj vertex from queue
		linkedListRemove(oddQ, adjVert);

	}

	//TESTING: print updated adjacency list
	for (int i = 0; i < N; i++)
	{
		cout << i << " -> ";
		linkedListPrint(mst[i]);
		cout << endl;
	}

	//delete Q
	linkedListDestroy(oddQ);

}


//find a euler circuit tour of mst
void findEuler(vector<int> &euler, LinkedList** mst)
{
	//create stack for holding visited vertices
	struct LinkedList *vStack = linkedListCreate();

	//start with an arbitrary vertex (city)
	int currVert = 0;

	do //while vStack is not empty
	{
		//if curr vert has no adj vertices
		if(linkedListGetSize(mst[currVert]) == 0)
		{
			//add to euler tour
			euler.push_back(currVert);
			//pop stack to create new curr vert
			currVert = linkedListFront(vStack);
			linkedListRemoveFront(vStack);
		}
		else //if curr vert has adj vertices
		{
			//push curr vert on stack
			linkedListAddFront(vStack, currVert);
			//choose any adj vertex of curr vert
			int neighbor = linkedListFront(mst[currVert]);
			//remove edge from adjacency list
			linkedListRemoveFront(mst[currVert]);
			linkedListRemove(mst[neighbor], currVert);
			//set neighbor as curr vert
			currVert = neighbor;
		}
	} while (!linkedListIsEmpty(vStack));


	//TEST -- print euler tour
	int vectSize = euler.size();
	cout << "Euler tour: ";
	for(int i = 0; i < vectSize; i++)
	{
		cout << euler[i] << " ";
	}

	//delete stack
	linkedListDestroy(vStack);
}



//transform euler circuit into hamiltonian cycle by shortcutting repeated vertices
void hamTransform(vector<int> &euler, int* ham, int N)
{
	//HamVisited is an int array in which each index represents a city. 
	//Value 0 means not visited; value 1 means visited
	int* hamVisited = new int[N];
	for(int i = 0; i < N; i++)
	{
		hamVisited[i] = 0;
	}

	////add starting vertex of euler to ham and ham visited
	//int currVert = euler[0];
	//ham[0] = currVert;
	//hamVisited[currVert] = 1;

	//loop through euler and add unvisited vertices to ham
	//shortcutting visited vertices

	int vectSize = euler.size();
	int j = 0; //ham index
	for(int i = 0; i < vectSize; i++)
	{
		int currEuler = euler[i];
		//if ham has not yet visited curr euler vertex, add to ham
		if (hamVisited[currEuler] == 0)
		{
			//add vertex to ham
			ham[j] = euler[i];
			//add vertex to ham visited
			hamVisited[currEuler] = 1;
			//increment ham index
			j++;
		}

	}

	//add starting vertex to end of ham tour
	ham[N] = ham[0];

	//TEST -- print ham tour
	cout << endl;
	cout << "Ham tour: ";
	for(int i = 0; i <= N; i++)
	{
		cout << ham[i] << " ";
	}

	//free allocated memory
	delete[] hamVisited;
}