/*	type.h

Defines the type to be stored in the data structure.  These macros
are for convenience to avoid having to search and replace/dup code
when you want to build a structure of doubles as opposed to ints
for example.
*/

#ifndef __TYPE_HPP
#define __TYPE_HPP


struct Vect {
	int cityNum;  	
	int key;			  			
};

typedef struct Vect Vect;

# ifndef TYPE
# define TYPE Vect
# endif

/* function used to compare two TYPE values to each other */
int compare(TYPE left, TYPE right);


#endif

