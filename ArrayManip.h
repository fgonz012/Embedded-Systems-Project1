/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#ifndef __ARRAY_MANIP_H__
#define __ARRAY_MANIP_H__

#include "bool.h"

void ArrayManip_copy( int* P, int size, int* J);
bool ArrayManip_areEqual( int* P, int sizeP, int* J);
bool ArrayManip_isNumIn(int* P, int sizeP, int number);
bool ArrayManip_doShareNum( int* p, int sizeP, int* J, int sizeJ);
bool ArrayManip_allElementsGreaterThan( int* P, int size, int number);
bool ArrayManip_allElementsLessThan( int* P, int size, int number);


bool ArrayManip_allElementsLessThan( int* P, int size, int number){
	for ( int i =0; i<size; i++){
		if ( P[i] >= number){ return false;}
	}
	
	return true;
}


void ArrayManip_copy( int* P, int size, int* J){//copies Array J into Array P
	
	for ( int i=0; i<size; i++){
		P[i] = J[i];
	}
}


bool ArrayManip_areEqual( int* P, int size, int* J){//checks if the two arrays are exactly the same
	for ( int i=0; i<size; i++){
		if ( P[i] != J[i]){return false;}
	}
	
	return true;
}


bool ArrayManip_isNumIn(int* P, int size, int number){//chesks if number is in array P
	for ( int i=0; i<size; i++){
		if ( P[i] == number ){return true;}
	}
	
	return false;
}

bool ArrayManip_doShareNum( int* P, int sizeP, int* J, int sizeJ){
	for ( int i=0; i<sizeP; i++){
		for ( int j=0; j<sizeJ; j++){
			if( P[i] == J[j]){return true;}
		}
	}
	
	return false;
}


bool ArrayManip_allElementsGreaterThan( int* P, int size, int number){
	for ( int i=0; i<size; i++){
		if ( P[i] <= number){ return false;}
	}
	
	return true;
}
#endif