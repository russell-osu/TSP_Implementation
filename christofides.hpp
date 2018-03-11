#ifndef CHRISTOFIDES_HPP
#define CHRISTOFIDES_HPP

#include "linkedList.hpp"
#include "dynArray.hpp"
#include <vector>

using std::vector;

void primMST(int** matrix, int N, struct LinkedList ** mst);
void updateKey(int city, int newKey, DynArr* heap);
void findMatching(int **matrix, LinkedList** mst, int* mstDegree, int N);
void findEuler(vector<int> &euler, LinkedList** mst);
void hamTransform(vector<int> &euler, int* ham, int N);



#endif
