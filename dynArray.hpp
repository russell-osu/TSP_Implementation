/* 	dynArray.h : Dynamic Array implementation. */
#ifndef DYNAMIC_ARRAY_INCLUDED
#define DYNAMIC_ARRAY_INCLUDED 1

#include "type.hpp"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};
typedef struct DynArr DynArr;


/* Dynamic Array Functions */
void initDynArr(DynArr *v, int capacity);
DynArr *newDynArr(int cap);

void freeDynArr(DynArr *v);
void deleteDynArr(DynArr *v);

void _dynArrSetCapacity(DynArr *v, int newCap);
int sizeDynArr(DynArr *v);

void addDynArr(DynArr *v, TYPE val);
TYPE getDynArr(DynArr *v, int pos);
void putDynArr(DynArr *v, int pos, TYPE val);
void swapDynArr(DynArr *v, int i, int  j);
void removeAtDynArr(DynArr *v, int idx);
int isEmptyDynArr(DynArr *v);

void copyDynArr(DynArr *source, DynArr *destination);

/* Heap-based Priority Queue Interface */
TYPE getMinHeap(DynArr *heap);
void addHeap(DynArr *heap, TYPE node, int* lookup);
void removeMinHeap(DynArr *heap, int* lookup);
void sortHeap(DynArr *heap, int* lookup);
void percolateUpHeap(DynArr *heap, int pos, int* lookup);

#endif
