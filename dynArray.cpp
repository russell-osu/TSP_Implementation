/*	dynArray.c: Dynamic Array implementation.
* CS261: Assignment 4/
* Name: Russell Moon
* Date: 11/05/2017
* Solution description: This is the dynamic array implementation
*	of a heap-based priority queue
*/


#include <assert.h>
#include <stdlib.h>
#include "dynArray.hpp"
//#include "stdio.h"

/* ************************************************************************
Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

param: 	v		pointer to the dynamic array
param:	cap 	capacity of the dynamic array
pre:	v is not null
post:	internal data array can hold cap elements
post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	v->data = new TYPE[capacity];  //(TYPE *)malloc(sizeof(TYPE) * capacity);
	assert(v->data != nullptr);

	v->size = 0;
	v->capacity = capacity;
}

/* Allocate and initialize dynamic array.

param:	cap 	desired capacity for the dyn array
pre:	none
post:	none
ret:	a non-null pointer to a dynArr of cap capacity
and 0 elements in it.
*/
DynArr* newDynArr(int cap)
{
	DynArr *r = new DynArr;//(DynArr *)malloc(sizeof(DynArr));
	assert(r != nullptr);
	initDynArr(r, cap);
	return r;
}

/* Deallocate data array in dynamic array.

param: 	v		pointer to the dynamic array
pre:	none
post:	d.data points to null
post:	size and capacity are 0
post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if (v->data != nullptr)
	{
		delete[] v->data; 	/* free the space on the heap */
		v->data = nullptr;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure.

param: 	v		pointer to the dynamic array
pre:	none
post:	the memory used by v->data is freed
post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	delete v;
}

/* Resizes the underlying array to be the size cap

param: 	v		pointer to the dynamic array
param:	cap		the new desired capacity
pre:	v is not null
post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{
	int i;

	/* Create a new underlying array */
	TYPE *newData = new TYPE[newCap]; //(TYPE*)malloc(sizeof(TYPE)*newCap);
	assert(newData != nullptr);

	/* copy elements to new data array */
	for (i = 0; i < v->size; i++)
		newData[i] = v->data[i];

	/* Delete the old underlying array */
	freeDynArr(v);
	/* update capacity and size and data */
	v->data = newData;
	v->capacity = newCap;
	v->size = i;
}

/* Get the size of the dynamic array

param: 	v		pointer to the dynamic array
pre:	v is not null
post:	none
ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

param: 	v		pointer to the dynamic array
param:	val		the value to add to the end of the dynamic array
pre:	the dynArry is not null
post:	size increases by 1
post:	if reached capacity, capacity is doubled
post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	/* Check to see if a resize is necessary */
	if (v->size >= v->capacity)
		_dynArrSetCapacity(v, 2 * v->capacity);

	v->data[v->size] = val;
	v->size++;
}

/*	Get an element from the dynamic array from a specified position

param: 	v		pointer to the dynamic array
param:	pos		integer index to get the element from
pre:	v is not null
pre:	v is not empty
pre:	pos < size of the dyn array and >= 0
post:	no changes to the dyn Array
ret:	value stored at index pos
*/
TYPE getDynArr(DynArr *v, int pos)
{
	//printf("Value of pos: %d\n", pos);
	//printf("array size: %d\n", sizeDynArr(v));
	assert(pos < v->size);
	assert(pos >= 0);

	return v->data[pos];
}

/*	Put an item into the dynamic array at the specified location,
overwriting the element that was there

param: 	v		pointer to the dynamic array
param:	pos		the index to put the value into
param:	val		the value to insert
pre:	v is not null
pre:	v is not empty
pre:	pos >= 0 and pos < size of the array
post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(pos < v->size);

	v->data[pos] = val;
}

/*	Swap two specified elements in the dynamic array

param: 	v		pointer to the dynamic array
param:	i,j		the elements to be swapped
pre:	v is not null
pre:	v is not empty
pre:	i, j >= 0 and i,j < size of the dynamic array
post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	TYPE  temp;

	assert(i < v->size);
	assert(j < v->size);

	temp = v->data[i];
	v->data[i] = v->data[j];
	v->data[j] = temp;
}

/*	Remove the element at the specified location from the array,
shifts other elements back one to fill the gap

param: 	v		pointer to the dynamic array
param:	idx		location of element to remove
pre:	v is not null
pre:	v is not empty
pre:	idx < size and idx >= 0
post:	the element at idx is removed
post:	the elements past idx are moved back one
*/
void
removeAtDynArr(DynArr *v, int idx)
{
	int i;

	for (i = idx; i < v->size - 1; ++i)
		v->data[i] = v->data[i + 1];

	if (idx >= 0 && idx < v->size)
		--v->size;
}

int isEmptyDynArr(DynArr* v)
{
	//validate array
	assert(v != 0);

	int isEmpty = 0; //create bool to return

					 //check if array is empty
	if (v->size < 1)
	{
		isEmpty = 1;
	}

	//return bool
	return isEmpty;
}

/*	Copy elements from a dynamic array to another dynamic array

param: 	source	pointer to the source dynamic array
param:	destination		pointer to the destination dynamic array
pre:	s is not null and s is not empty
post:	destination is initialized
post: 	the elements from source are copied to destination
*/
void copyDynArr(DynArr *source, DynArr *destination)
{
	int i;
	assert(source->size > 0);
	initDynArr(destination, source->capacity);
	/* copy elements to destination array */
	for (i = 0; i < source->size; i++)
		destination->data[i] = source->data[i];

	destination->size = source->size;
}

/* ************************************************************************
Heap-based Priority Queue Implementation
************************************************************************ */

/* internal function prototypes */
int _smallerIndexHeap(DynArr *heap, int i, int j);
void _adjustHeap(DynArr *heap, int max, int pos);

/*	Get the index of the smaller node between two nodes in a heap

param: 	heap	pointer to the heap
param:	i	index of one node
param:	j	index of other node
pre:	i < size and j < size
ret:	the index of the smaller node
*/
int _smallerIndexHeap(DynArr *heap, int i, int j)
{
	assert(i < sizeDynArr(heap));
	assert(j < sizeDynArr(heap));
	if (compare(getDynArr(heap, i), getDynArr(heap, j)) == -1)
		return i;
	else
		return j;
}

/*	Get the first node, which has the min priority, from the heap

param: 	heap	pointer to the heap
pre:	heap is not empty
ret:	value of first node
*/
TYPE getMinHeap(DynArr *heap)
{
	/* FIXME */						//COMPLETED

									//ensure that heap has at least one element
	assert(sizeDynArr(heap) > 0);

	//retrieve and return value
	TYPE minVal = getDynArr(heap, 0);
	return minVal;
}

/*	Add a node to the heap

param: 	heap	pointer to the heap
param: 	node	node to be added to the heap
pre:	heap is not null
post:	node is added to the heap
*/
void addHeap(DynArr *heap, TYPE node)
{
	/* FIXME */					//COMPLETED

								//ensure heap is not null
	assert(heap != NULL);

	//add node to end of heap
	addDynArr(heap, node);

	//point position to index of newly added element (1 less than size)
	int nodeIndex = sizeDynArr(heap) - 1;
	int parentIndex;
	int swappingFinished = 0; //bool for terminating loop

							  //percolate up until node is in the correct position in the heap
	while (nodeIndex != 0 && !swappingFinished)
	{
		//find index of parent
		parentIndex = (nodeIndex - 1) / 2;
		//compare new value with parent's value; if less, swap
		if (compare(getDynArr(heap, nodeIndex), getDynArr(heap, parentIndex)) == -1)
		{
			swapDynArr(heap, nodeIndex, parentIndex);
			//set new val's index equal to parent's index
			nodeIndex = parentIndex;
		}
		else //no more swaps needed
		{
			swappingFinished = 1;
		}
	}

}

/*	Adjust heap to maintain heap property

param: 	heap	pointer to the heap
param: 	max		max index of the heap nodes in the dynamic array
param: 	pos		position index where the adjustment starts
pre:	none
post:	heap property is maintained for nodes from index pos to index max
*/
void _adjustHeap(DynArr *heap, int max, int pos)
{
	/* FIXME */

	//calculate indices for left and right children
	int leftChPos = (pos * 2) + 1;
	int rightChPos = (pos * 2) + 2;
	TYPE currentVal = getDynArr(heap, pos); //value of current position

											//determine how many children position has
	if (rightChPos < max) //if there are two children
	{
		//get index and value of smallest child
		int smallestChPos = _smallerIndexHeap(heap, leftChPos, rightChPos);
		TYPE smallestChVal = getDynArr(heap, smallestChPos);
		//determine if downward swap needed and call adjust heap again
		if (compare(currentVal, smallestChVal) == 1) //curr val > smallest child
		{
			//swap values (percolate down) and adjust heap
			swapDynArr(heap, pos, smallestChPos);
			_adjustHeap(heap, max, smallestChPos);
		}
	}

	else if (leftChPos < max) //if there's only one child
	{
		TYPE leftChVal = getDynArr(heap, leftChPos);
		//determine if downward swap needed and call adjust heap again
		if (compare(currentVal, leftChVal) == 1) //curr val > left child
		{
			//swap values (percolate down) and adjust heap
			swapDynArr(heap, pos, leftChPos);
			_adjustHeap(heap, max, leftChPos);
		}
	}

	//else, position has no children; no adjustment needed

}





/*	Remove the first node, which has the min priority, from the heap

param: 	heap	pointer to the heap
pre:	heap is not empty
post:	the first node is removed from the heap
*/
void removeMinHeap(DynArr *heap)
{
	/* FIXME */				//COMPLETED

							//ensure heap is not empty
	assert(sizeDynArr(heap) > 0);

	int lastIndex = sizeDynArr(heap) - 1;
	TYPE lastElement = getDynArr(heap, lastIndex);

	//put the last element at the top of the heap,
	//effectively removing the first element
	putDynArr(heap, 0, lastElement);

	//adjust heap
	_adjustHeap(heap, lastIndex, 0);

	//remove last element
	removeAtDynArr(heap, lastIndex);


}


/* builds a heap from an arbitrary dynArray

param: v	dynamicArray
pre:	v is not empty
post: v is a proper heap
*/

void _buildHeap(DynArr *heap) //POTENTIALLY BUGGY FUNCTION
{
	/* FIXME */				//COMPLETED

	//ensure heap is not empty
	assert(sizeDynArr(heap) > 0);

	//calculate index of highest node with children
	int highParentIdx = sizeDynArr(heap) / 2 - 1;

	//step back through indices, adjusting each node
	for (int i = highParentIdx; i >= 0; i--)
	{
		_adjustHeap(heap, sizeDynArr(heap), i);
	}


}
/*
In-place sort of the heap

param: heap		pointer to the heap
pre: heap is not empty
post: the dynArr is in reverse sorted order
*/

void sortHeap(DynArr *heap) //POTENTIALLY BUGGY FUNCTION
{
	/*FIXME*/		//COMPLETED

	//ensure heap is not empty
	assert(sizeDynArr(heap) > 0);

	//build heap from unsorted array
	_buildHeap(heap);

	//step through heap, swapping last element in heap with
	//first element (top of heap),
	int maxIndex = sizeDynArr(heap) - 1;
	for (int i = maxIndex; i > 0; i--)
	{
		swapDynArr(heap, i, 0);
		_adjustHeap(heap, i, 0);
	}

}



int compare(TYPE left, TYPE right)
{
	if (left.key < right.key)
		return -1;
	if (left.key > right.key)
		return 1;

	return 0;
}
