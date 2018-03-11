/* CS261- Assignment 3 - Part 1/
* Name: Russell Moon
* Date: 10/06/2017
* Solution description: This is the linked list implementation
*	of a deque and a bag
*/

#include "linkedList.hpp"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE_2 value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};



/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinels' next and prev should point to eachother or NULL
* as appropriate.
*/
static void init(struct LinkedList* list) {
	// FIXME: you must write this			//COMPLETE	

	//allocate memory for sentinels and confirm allocation
	list->frontSentinel = new Link;
	list->backSentinel = new Link;
	assert(list->frontSentinel);
	assert(list->backSentinel);

	//initialize size
	list->size = 0;

	//initialize next and prev links in front and back sentinels
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = 0;
	list->backSentinel->prev = list->frontSentinel;
	list->backSentinel->next = 0;
}



/**
* Adds a new link with the given value before the given link and
* increments the list's size.
*/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE_2 value)
{
	// FIXME: you must write this  //COMPLETE

	//create and allocate space for new link
	struct Link* newLink = new Link;
	assert(newLink);
	newLink->value = value;

	//connect new link to existing elements in deque
	newLink->next = link;
	newLink->prev = link->prev;

	//update next and prev for prior head or tale (order is important)
	link->prev->next = newLink;
	link->prev = newLink;

	//update size
	list->size++;
}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this   //COMPLETE

	//connect links/sentinenls surrounding link to be removed
	link->prev->next = link->next;
	link->next->prev = link->prev;

	//delete link to be removed
	link->next = 0;
	link->prev = 0;
	delete link;

	//update size
	list->size--;
}

/**
* Allocates and initializes a list.
*/
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = new LinkedList;
	init(newDeque);
	return newDeque;
}

/**
* Deallocates every link in the list including the sentinels,
* and frees the list itself.
*/
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	delete list->frontSentinel;
	delete list->backSentinel;
	delete list;
}

/**
* Adds a new link with the given value to the front of the deque.
*/
void linkedListAddFront(struct LinkedList* list, TYPE_2 value)
{
	// FIXME: you must write this	//COMPLETE

	//add link before head of deque
	addLinkBefore(list, list->frontSentinel->next, value);

}

/**
* Adds a new link with the given value to the back of the deque.
*/
void linkedListAddBack(struct LinkedList* list, TYPE_2 value)
{
	// FIXME: you must write this	//COMPLETE

	//add link before back sentinel
	addLinkBefore(list, list->backSentinel, value);
}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE_2 linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this	//COMPLETE

	//make sure list has at least one element
	assert(!linkedListIsEmpty(list));

	//return value of head
	return list->frontSentinel->next->value;
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE_2 linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this

	//make sure list has at least one element
	assert(!linkedListIsEmpty(list));

	//return value of tail
	return list->backSentinel->prev->value;
}

/**
* Removes the link at the front of the deque.
*/
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this	//COMPLETE

	//make sure list has at least one element
	assert(!linkedListIsEmpty(list));

	//send head of list to remove function
	removeLink(list, list->frontSentinel->next);
}

/**
* Removes the link at the back of the deque.
*/
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this	//COMPLETE

	//make sure list has at least one element
	assert(!linkedListIsEmpty(list));

	//send tail of list to remove function
	removeLink(list, list->backSentinel->prev);
}

//returns size of linked list
int linkedListGetSize(LinkedList* list)
{
	return list->size;
}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this	//COMPLETE

	if (list->size == 0)
	{
		return 1;
	}

	return 0;
}

/**
* Prints the values of the links in the deque from front to back.
*/
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this	//COMPLETE

	//make sure list has at least one element
	//assert(!linkedListIsEmpty(list));

	//loop through deque
	struct Link* dequePtr = list->frontSentinel;
	for (int i = 1; i <= list->size; i++)
	{
		TYPE_2 val = dequePtr->next->value;
		printf("%d ", val);
		//increment deque pointer
		dequePtr = dequePtr->next;
	}

	printf("\n");
}

/**
* Adds a link with the given value to the bag.
*/
void linkedListAdd(struct LinkedList* list, TYPE_2 value)
{
	// FIXME: you must write this	//COMPLETE

	//add element to front of deque
	linkedListAddFront(list, value);
}

/**
* Returns 1 if a link with the value is in the bag and 0 otherwise.
*/
int linkedListContains(struct LinkedList* list, TYPE_2 value)
{
	// FIXME: you must write this	//COMPLETE

	//make sure list has at least one element
	assert(!linkedListIsEmpty(list));


	//loop through bag
	struct Link* dequePtr = list->frontSentinel;
	for (int i = 1; i <= list->size; i++)
	{
		TYPE_2 val = dequePtr->next->value;

		//if match is found, return true
		if (EQ(val, value))
		{
			return 1;
		}

		//increment deque pointer
		dequePtr = dequePtr->next;
	}

	return 0;
}

/**
* Removes the first occurrence of a link with the given value.
*/
void linkedListRemove(struct LinkedList* list, TYPE_2 value)
{
	// FIXME: you must write this	//COMPLETE

	//make sure list has at least one element
	assert(!linkedListIsEmpty(list));

	//loop through bag
	struct Link* dequePtr = list->frontSentinel;
	for (int i = 1; i <= list->size; i++)
	{
		TYPE_2 val = dequePtr->next->value;

		//if match is found, remove link
		if (EQ(val, value))
		{
			removeLink(list, dequePtr->next);
			//set i equal to size to force loop to end
			i = list->size;
		}

		//increment deque pointer
		dequePtr = dequePtr->next;
	}
}
