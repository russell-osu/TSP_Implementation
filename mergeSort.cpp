#include "mergeSort.hpp"


//Merge Sort
//psuedocode for merge sort from CLRS_3e, p34
void mergeSort(vector<TYPE> &vect, int p, int r)
{
	//as long as vector size is greater than one
	if (p < r)
	{
		//find the midpoint of the vector (int div guarantees floor)
		int q = (p + r) / 2;
		//call mergeSort on first half of vector
		mergeSort(vect, p, q);
		//call mergeSort on second half of vector
		mergeSort(vect, q + 1, r);
		//merge both halves
		merge(vect, p, q, r);
	}
}


//psuedocode for merge sort from CLRS_3e, p31
void merge(vector<TYPE> &vect, int p, int q, int r)
{
	int leftSize = q - p + 1;
	int rightSize = r - q;

	//create left and right vectors(decks) from original vector
	vector<TYPE> left;
	vector<TYPE> right;
	for (int i = 0; i < leftSize; i++)
	{
		left.push_back(vect[p + i]);
	}

	for (int j = 0; j < rightSize; j++)
	{
		right.push_back(vect[q + 1 + j]);
	}

	//add sentinels to end of left and right decks to simplify algorithm
	TYPE sentinel;
	sentinel.key = SENTINEL;
	left.push_back(sentinel);
	right.push_back(sentinel);

	//loop from p to r and merge elements back to original vect
	int i = 0; //counter for left deck
	int j = 0; //counter for right deck

	for (int k = p; k <= r; k++)
	{
		//compare left and right decks and merge accordingly
		//if (left[i] <= right[j])
		if (compare(left[i], right[j]) == -1 || compare(left[i], right[j]) == 0)
		{
			vect[k] = left[i];
			i++;
		}
		else //if right deck is smaller
		{
			vect[k] = right[j];
			j++;
		}

	}

}

//compare function for struct TYPE
int compare(TYPE left, TYPE right)
{
	if (left.key < right.key)
		return -1;
	else if (left.key > right.key)
		return 1;
	else
		return 0;
}