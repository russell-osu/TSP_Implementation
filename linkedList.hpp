#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#ifndef TYPE_2
#define TYPE_2 int
#endif


#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif

struct LinkedList;

struct LinkedList* linkedListCreate();
void linkedListDestroy(struct LinkedList* list);
void linkedListPrint(struct LinkedList* list);

// Deque interface

int linkedListIsEmpty(struct LinkedList* list);
void linkedListAddFront(struct LinkedList* list, TYPE_2 value);
void linkedListAddBack(struct LinkedList* list, TYPE_2 value);
TYPE_2 linkedListFront(struct LinkedList* list);
TYPE_2 linkedListBack(struct LinkedList* list);
void linkedListRemoveFront(struct LinkedList* list);
void linkedListRemoveBack(struct LinkedList* list);
int linkedListGetSize(struct LinkedList* list);

// Bag interface

void linkedListAdd(struct LinkedList* list, TYPE_2 value);
int linkedListContains(struct LinkedList* list, TYPE_2 value);
void linkedListRemove(struct LinkedList* list, TYPE_2 value);

#endif