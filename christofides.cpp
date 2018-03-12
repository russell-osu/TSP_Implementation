/*Implementation files for Christofides Algorithm*/

#include "christofides.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

// build a minimum spanning tree from graph represented by matrix
void primMST(int** matrix, int N, struct LinkedList ** mst)
{
	//create min heap with city numbers and key 
	DynArr* vectHeap = newDynArr(N);
	//create key array (for easily retrieving key value)
	int* key = new int[N];
	//create array for tracking if vertex has been removed from heap
	int* inHeap = new int[N];
	//city to serve as root of MST
	int startCity = 0;
	//create array for tracking previous city
	int* prevCity = new int[N];
	prevCity[startCity] = -1; //first city has no previous city


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
	updateKey(startCity, 0, vectHeap);
	key[startCity] = 0;


	////TESTING MIN HEAP FUNCTIONALITY
	//for (int i = 0; i < 76; i++)
	//{
	//	struct Vect u = getMinHeap(vectHeap);
	//	removeMinHeap(vectHeap); //remove from heap
	//	cout << "removed from heap: " << u.cityNum << " key: " << u.key << endl;
	//}


	//build MST
	while (!isEmptyDynArr(vectHeap))
	{
		//get and remove city with lowest key weight from heap
		struct Vect u = getMinHeap(vectHeap);
		removeMinHeap(vectHeap); //remove from heap
		inHeap[u.cityNum] = 0; //remove from in-heap tracking array

		//search for vertices adjacent to u in matrix
		for (int v = 0; v < N; v++)
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

	////TEST print out prevCity array
	//for(int i = 0; i < N; i++)
	//{
	//	cout << "i: " << i << " prev i: " << prevCity[i] << endl;
	//}


	//Add previous vertices to adjacency list
	int mstWeight = 0;
	for (int i = 0; i < N; i++)
	{
		if(i != startCity)
		{
			linkedListAddBack(mst[prevCity[i]], i);
			linkedListAddBack(mst[i], prevCity[i]);
			mstWeight += matrix[i][prevCity[i]];
		}
	}

	cout << "MST weight: " << mstWeight << endl;

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
	//int lastIndex = sizeDynArr(heap) - 1;

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
	percolateUpHeap(heap,currIndex);

}


//find a min-weight perfect matching of odd-parity 
//vertices in mst and add to mst
void findMatching(int **matrix, LinkedList** mst, int* mstDegree, int N)
{

	//create queue for holding odd parity vertices
	struct LinkedList *oddQ = linkedListCreate();

	//add odd-parity vertices to queue
	for (int i = 0; i < N; i++)
	{
		if (mstDegree[i] % 2 != 0)
		{
			linkedListAddBack(oddQ, i);
		}

	}


	//loop through queue until empty, adding edges to MST
	while (!linkedListIsEmpty(oddQ))
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
		for (int i = 0; i < qSize; i++)
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


		//add edge to mst 
		linkedListAddBack(mst[currVert], adjVert);
		linkedListAddBack(mst[adjVert], currVert);

		//remove adj vertex from queue
		linkedListRemove(oddQ, adjVert);

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
		if (linkedListGetSize(mst[currVert]) == 0)
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


	//delete stack
	linkedListDestroy(vStack);
}



//transform euler circuit into hamiltonian cycle by shortcutting repeated vertices
void hamTransform(vector<int> &euler, int* ham, int N)
{
	//HamVisited is an int array in which each index represents a city. 
	//Value 0 means not visited; value 1 means visited
	int* hamVisited = new int[N];
	for (int i = 0; i < N; i++)
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
	for (int i = 0; i < vectSize; i++)
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

	//free allocated memory
	delete[] hamVisited;
}