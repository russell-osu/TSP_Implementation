#ifndef MERGESORTREV_HPP
#define MERGESORTREV_HPP

#include "type.hpp"
#include<vector>

using std::vector;

//define constant for sentinel 
#define SENTINEL 10005543289

void mergeSort(vector<TYPE> &vect, int p, int r);

void merge(vector<TYPE> &vect, int p, int q, int r);


#endif
