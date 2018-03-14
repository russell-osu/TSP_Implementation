//---------------------------------------------------------------------------
//	CS 325 - Functions related to the twoOpt Algorithm the TSP Project
//----------------------------------------------------------------------------

#include "utilities.hpp"
#include "twoOpt.hpp"
#include "threeOpt.hpp"

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
// --- Function threeOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour with a three-opt approximation
// --------------------------------------------------------------------
int threeOpt(int* tour, int** matrix, int N){

    bool changeMade = false;
    int x = 1;
    int y = 0;
    int z = 0;

    int reduction = 0;
    int tourLength;
    int option;

    tourLength = 0;
    for (int i = 0; i < N; i++){
        tourLength += matrix[tour[i]][tour[i+1]];
    }
    cout << endl;

    // starting with the first edge, iterate through all of the existing edges
    for(x = 1; x < (N-4); x++){
        changeMade = false; //(reset) only true is when restarting at j=1

        y = x + 1;

        //compare this edge with all other edges following it (except next one)
        while(!changeMade && (y < (N-3))) {
            y++;

            z = y + 1;
            while(!changeMade && (z < N-1) && !((z ==(N-1) && x == 1))) {
                            // Also, Do not compare first and last edge of tour
                z++;
// TESTING
 cout << endl << "x = " << x << ", Current Tour Length = " << tourLength;

                // find best option of all possible swaps at x, y & z
                option = findMinOpt(tour, x, y, z, matrix, reduction);

                if(reduction > 0){
                  tourLength = tourLength - reduction;
                  switch(option){

  /* --- Running 3-Opt Cases Only ---
                    // Two-Opt Cases
                    case 1: swapEdges(tour, y, z);
                            break;
                    case 2: swapEdges(tour, x, z);
                            break;
                    case 3: swapEdges(tour, x, y);
                            break;
 */ // ----------------------------
                    case 4: splice(tour, x, y, z);
                            break;
                    case 5: reversePath(tour, x, y);
                            reversePath(tour, y, z);
                            break;
                    case 6: reversePath(tour, y, z);
                            splice(tour, x, y, z);
                            break;
                    case 7: reversePath(tour, x, y);
                            splice(tour, x, y, z);
                            break;
                    default:     ; // Keep the existing tour
                  }
                  //   changeMade = true;  // drop out of the y & z loops
                  //   x = 0;              // restart the x loop
                } // end if

            }  // end of z while loop
        }  // end of y while loop

            // TESTING ---  print intermediate tour lengths ---------
         //       cout << endl;
         //       cout << "Current Tour Length = " << tourLength;
            // -----------------------------------------------------

    }  // end of for loop
    return tourLength;
}


// --------------------------------------------------------------------
// --- Function KOpt
// --- Takes in existing tour data, city coordinates and number of cities
// --- Revises the tour with a combined two-opt and  three-opt approximation
// --------------------------------------------------------------------
int KOpt(int* tour, int** matrix, int N){

    bool changeMade = false;
    int x = 1;
    int y = 0;
    int z = 0;

    int reduction = 0;
    int tourLength;
    int option;

    tourLength = 0;
    for (int i = 0; i < N; i++){
        tourLength += matrix[tour[i]][tour[i+1]];
    }
cout << endl;

    // starting with the first edge, iterate through all of the existing edges
    for(x = 1; x < (N-4); x++){
        changeMade = false; //(reset) only true is when restarting at j=1

        y = x + 1;

        //compare this edge with all other edges following it (except next one)
        while(!changeMade && (y < (N-3))) {
            y++;

            z = y + 1;
            while(!changeMade && (z < N-1) && !((z ==(N-1) && x == 1))) {
                            // Also, Do not compare first and last edge of tour
                z++;
// TESTING
 cout << endl << "x = " << x << ", Current Tour Length = " << tourLength;

                // find best option of all possible swaps at x, y & z
                option = findMinOptK(tour, x, y, z, matrix, reduction);

                if(reduction > 0){
                  tourLength = tourLength - reduction;
                  switch(option){

                    // Two-Opt Cases
                    case 1: swapEdges(tour, y, z);
                            break;
                    case 2: swapEdges(tour, x, z);
                            break;
                    case 3: swapEdges(tour, x, y);
                            break;
                    // Three-Opt Cases
                    case 4: splice(tour, x, y, z);
                            break;
                    case 5: reversePath(tour, x, y);
                            reversePath(tour, y, z);
                            break;
                    case 6: reversePath(tour, y, z);
                            splice(tour, x, y, z);
                            break;
                    case 7: reversePath(tour, x, y);
                            splice(tour, x, y, z);
                            break;
                    default:     ; // Keep the existing tour
                  }
                  //   changeMade = true;  // drop out of the y & z loops
                  //   x = 0;              // restart the x loop
                } // end if

            }  // end of z while loop
        }  // end of y while loop

            // TESTING ---  print intermediate tour lengths ---------
         //       cout << endl;
         //       cout << "Current Tour Length = " << tourLength;
            // -----------------------------------------------------

    }  // end of for loop
    return tourLength;
}



// --------------------------------------------------------------------
// --- Function reversePath
// --- Takes in tour data, indexes of the tour
// --- Returns the tour with the direction of the indicated section reversed
// --- Includes nodes x thru (y-1) in the reversed path
// --------------------------------------------------------------------
void reversePath(int* tour, int x, int y){

    int midPath[16000];

    // create a sub-path that is between the cut points and reverse it
    for(int k = 0; k < y-x; k++){
	midPath[k] = tour[y-k-1];
    }
    // splice the path back into the tour
    for(int k = 0; k < y-x; k++){
	  tour[k+x] = midPath[k];
    }
    return;
}





// --------------------------------------------------------------------
// --- Function findMinOpt       (Used with three opt)
// --- Take in the tour, adjacency matrix and 3 nodes for 3-Opt consideration
// --- Compares change of length of each of 4 potential edge swaps
// --- and returns the Case that results in the greatest reduction (if any)
// --------------------------------------------------------------------
int findMinOpt(int* tour, int x, int y, int z, int** matrix, int &reduction){
    int minOpt = 0;  // default to the original tour being the shortest Case
    int minDist;

//    int d1, d2, d3;

    int d0, d4, d5, d6, d7;

/* --- Running 3-Opt Cases Only ---
    d1 = matrix[tour[x-1]][tour[x]] + matrix[tour[y-1]][tour[z-1]]
            + matrix[tour[y]][tour[z]];
    d2 = matrix[tour[x-1]][tour[z-1]] + matrix[tour[y-1]][tour[y]]
            + matrix[tour[x]][tour[z]];
    d3 = matrix[tour[x-1]][tour[y-1]] + matrix[tour[x]][tour[y]]
            + matrix[tour[z-1]][tour[z]];
*/ // --------------------------------------------

    d0 = matrix[tour[x-1]][tour[x]] + matrix[tour[y-1]][tour[y]]
            + matrix[tour[z-1]][tour[z]];
    d4 = matrix[tour[x-1]][tour[y]] + matrix[tour[x]][tour[z-1]]
            + matrix[tour[y-1]][tour[z]];
    d5 = matrix[tour[x-1]][tour[y-1]] + matrix[tour[x]][tour[z-1]]
            + matrix[tour[y]][tour[z]];
    d6 = matrix[tour[x-1]][tour[z-1]] + matrix[tour[x]][tour[y]]
            + matrix[tour[y-1]][tour[z]];
    d7 = matrix[tour[x-1]][tour[y]] + matrix[tour[y-1]][tour[z-1]]
            + matrix[tour[x]][tour[z]];

    minDist = d0;

/* --- Running 3-Opt Cases Only
    if(d1 < minDist){
        minDist = d1;
        minOpt = 1;
    }
    if(d2 < minDist){
        minDist = d2;
        minOpt = 2;
    }
    if(d3 < minDist){
        minDist = d3;
        minOpt = 3;
    }
 */ // --------------------------

    if(d4 < minDist){
        minDist = d4;
        minOpt = 4;
    }
    if(d5 < minDist){
        minDist = d5;
        minOpt = 5;
    }
    if(d6 < minDist){
        minDist = d6;
        minOpt = 6;
    }
    if(d7 < minDist){
        minDist = d7;
        minOpt = 7;
    }

    reduction = d0 - minDist;

    return minOpt;
}




// --------------------------------------------------------------------
// --- Function findMinOptK       (used with K Opt)
// --- Take in the tour, adjacency matrix and 3 nodes for 3-Opt consideration
// --- Compares change of length of each of 7 potential edge swaps
// --- and returns the Case that results in the greatest reduction (if any)
// --------------------------------------------------------------------
int findMinOptK(int* tour, int x, int y, int z, int** matrix, int &reduction){
    int minOpt = 0;  // default to the original tour being the shortest Case
    int minDist;

    int d1, d2, d3;

    int d0, d4, d5, d6, d7;

    d1 = matrix[tour[x-1]][tour[x]] + matrix[tour[y-1]][tour[z-1]]
            + matrix[tour[y]][tour[z]];
    d2 = matrix[tour[x-1]][tour[z-1]] + matrix[tour[y-1]][tour[y]]
            + matrix[tour[x]][tour[z]];
    d3 = matrix[tour[x-1]][tour[y-1]] + matrix[tour[x]][tour[y]]
            + matrix[tour[z-1]][tour[z]];

    d0 = matrix[tour[x-1]][tour[x]] + matrix[tour[y-1]][tour[y]]
            + matrix[tour[z-1]][tour[z]];
    d4 = matrix[tour[x-1]][tour[y]] + matrix[tour[x]][tour[z-1]]
            + matrix[tour[y-1]][tour[z]];
    d5 = matrix[tour[x-1]][tour[y-1]] + matrix[tour[x]][tour[z-1]]
            + matrix[tour[y]][tour[z]];
    d6 = matrix[tour[x-1]][tour[z-1]] + matrix[tour[x]][tour[y]]
            + matrix[tour[y-1]][tour[z]];
    d7 = matrix[tour[x-1]][tour[y]] + matrix[tour[y-1]][tour[z-1]]
            + matrix[tour[x]][tour[z]];

    minDist = d0;

    if(d1 < minDist){
        minDist = d1;
        minOpt = 1;
    }
    if(d2 < minDist){
        minDist = d2;
        minOpt = 2;
    }
    if(d3 < minDist){
        minDist = d3;
        minOpt = 3;
    }

    if(d4 < minDist){
        minDist = d4;
        minOpt = 4;
    }
    if(d5 < minDist){
        minDist = d5;
        minOpt = 5;
    }
    if(d6 < minDist){
        minDist = d6;
        minOpt = 6;
    }
    if(d7 < minDist){
        minDist = d7;
        minOpt = 7;
    }

    reduction = d0 - minDist;

    return minOpt;
}





// --------------------------------------------------------------------
// --- Function splice
// --- Takes in tour data, indexes of the tour
// --- Starts with the x-y-path before the y-z-path and is
// --- changed so that the old x-y-path will follow the old y-z-path
// --------------------------------------------------------------------
void splice(int* tour, int x, int y, int z){

    int midPath1[16000];
    int midPath2[16000];

    for(int k = 0; k < (y-x); k++){
        midPath1[k] = tour[k+x];
    }
    for(int k = 0; k < (z-y); k++){
        midPath2[k] = tour[k+y];
    }

    // reconstruct the tour with path2 before path1
    for(int k = x; k <= (x+z-y-1); k++){
        tour[k] = midPath2[k-x];
    }
    for(int k = (x+z-y); k < z; k++){
        tour[k] = midPath1[k-(x+z-y)];
    }
    return;
}
