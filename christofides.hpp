#ifndef CHRISTOFIDES_HPP
#define CHRISTOFIDES_HPP

#include "linkedList.hpp"
#include "dynArray.hpp"
#include <vector>

using std::vector;

void primMST(int** matrix, int N, struct LinkedList ** mst, int firstVert);
void updateKey(int city, int newKey, DynArr* heap, int* lookup, int N);
void findMatching(int **matrix, LinkedList** mst, int* mstDegree, int N);
void findEuler(vector<int> &euler, LinkedList** mst);
void hamTransform(vector<int> &euler, int* ham, int N);



#endif
