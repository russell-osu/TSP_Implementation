//---------------------------------------------------------------------------
//	CS 325 - Functions related to the twoOpt Algorithm the TSP Project
//----------------------------------------------------------------------------

#include "utilities.hpp"
#include "twoOpt.hpp"

#include "utilities.hpp"

#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::string;


// --------------------------------------------------------------------
// --- Function twoOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour with a full two-opt approximation
// --- Starts back at the beginning with every change (swap) of the tour
// --------------------------------------------------------------------
int twoOpt(int* tour, int** matrix, int N){

    bool changeMade = false;
    int j = 1;
    int k = 0;
    int reduction = 0;
    int tourLength;

    tourLength = 0;
    for (int i = 0; i < N; i++){
        tourLength += matrix[tour[i]][tour[i+1]];
    }

    // starting with the first edge, iterate through all of the existing edges
    for(j = 1; j < (N-1); j++){
        changeMade = false; //(reset) only true is when restarting at j=1
        k = j + 1;

        //compare this edge with all other edges following it (except next one)
        while(!changeMade && (k < N) && !((k ==(N-1) && j == 1))) {
                            // Also, Do not compare first and last edge of tour
            k++;

            // get the difference between the old path and the new path
            reduction = pathDiff(tour, j, k, matrix);

            if(reduction > 0){
                tourLength -= reduction;// calculated for intermediate tracking
                swapEdges(tour, j, k);   // new tour is shorter
                changeMade = true;  // drop out of the k loop
                j = 0;              // restart the j loop
            }

        }  // end of while loop



            // TESTING ---  print intermediate tour lengths ---------
                cout << endl;
                cout << "Current Tour Length (Full) = " << tourLength;
            // ------------------------------------------------------

    }  // end of for loop
    return tourLength;
}


// --------------------------------------------------------------------
// --- Function pseudoTwoOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour using the general 2-Opt Method
// --- But does not return to the beginning when changes are made
// --- Continues from the current position Through the successively revised tour
// --------------------------------------------------------------------
int pseudoTwoOpt(int* tour, int** matrix, int N){

    bool changeMade = false;
    int j = 1;
    int k = 0;
    int reduction = 0;
    int tourLength;

    tourLength = 0;
    for (int i = 0; i < N; i++){
       tourLength += matrix[tour[i]][tour[i+1]];
    }

    // starting with the first edge, iterate through all of the existing edges
    for(j = 1; j < (N-1); j++){
        changeMade = false; //(reset) only true is when restarting at j=1
        k = j + 1;

        //compare this edge with all other edges following it (except next one)
        while(!changeMade && (k < N) && !((k ==(N-1) && j == 1))) {
                            // Also, Do not compare first and last edge of tour
            k++;

            // get the difference between the old path and the new path
            reduction = pathDiff(tour, j, k, matrix);

            if(reduction > 0){  // new tour is shorter
                tourLength -= reduction;// calculated for intermediate tracking
                swapEdges(tour, j, k);
    //            changeMade = true;  // drop out of the k loop
    //            j = 0;              // restart the j loop
            }

        }  // end of while loop

                // TESTING ---  print intermediate tour lengths ---------
                    cout << endl;
                    cout << "Current Tour Length (Pseudo) = " << tourLength;
                // ------------------------------------------------------

    }  // end of for loop
    return tourLength;
}



// --------------------------------------------------------------------
// --- Function swapEdges
// --- Takes in tour data, indexes of the tour
// --- Returns the tour with a two-Opt swap completed at those indexes
// --------------------------------------------------------------------
void swapEdges(int* tour, int x, int y){

    int midPath[16000];  // would it be faster to create this in main
                         // once and pass the pointer to it?

    // create a sub-path that is between the cut points and reverse it
    for(int k = 0; k < y-x; k++){
	midPath[k] = tour[y-k-1];
    }
    // splice the path back into the tour
    for(int k = 0; k < y-x; k++){
	  tour[k+x] = midPath[k];
    }
//cout << endl << "Edges Swapped" << endl;
    return;
}

// -------------------------------------------------------------------
// --- Function pathDiff
// --- Takes in tour data, indexes of the tour, and city adjacency matrix,
// --- Returns the difference in length making a two-Opt swap would produce
// --------------------------------------------------------------------
int pathDiff(int* tour, int j, int k, int** matrix){

    int oldEdge1, oldEdge2, newEdge1, newEdge2;

    // Calculate the squares of the edges
    oldEdge1 = matrix[tour[j]][tour[j-1]];
    oldEdge2 = matrix[tour[k]][tour[k-1]];
    newEdge1 = matrix[tour[j-1]][tour[k-1]];
    newEdge2 = matrix[tour[k]][tour[j]];

    return (oldEdge1 + oldEdge2) - (newEdge1 + newEdge2);
}

/*
// -------------------------------------------------------------------
// --- Function edgeLength
// --- Takes in tour data, indexes of the tour, and city coordinates,
// --- Returns distances between the cities
// --------------------------------------------------------------------
int edgeLength(int* tour, int j, int k, int** matrix){

    int sqEdge;

    // Calculate the squares of the edges
    sqEdge = pow((citiesX[tour[j]] - citiesX[tour[k]]), 2) +
			pow((citiesY[tour[j]] - citiesY[tour[k]]), 2);

    return round(sqrt(sqEdge));
}
*/
