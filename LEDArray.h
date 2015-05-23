/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#ifndef __LED_ARRAY_H__
#define __LED_ARRAY_H__

#include "bool.h"
#include "LightData.c"
#include <stdlib.h>
#include "bit16.h"
#include "colors.h"


typedef struct LED_Light{
	
	int number;
	bool isOn;
	bool isBlinking;
	color LEDcolor;
	
}LED_Light;

LED_Light* LED_Lights[128];
int sizeof_LED_Lights = sizeof(LED_Lights) / sizeof(*LED_Lights);


//ALL PUBLIC
void LEDArray_Init();
void LEDArray_LightLED(int num, color col);
void LEDArray_LightArrayMatrix();
void LEDArray_TurnOffArray();
void LEDArray_TurnOffLED();
void LEDArray_LightArray(int *P, int size, color col);
void LEDArray_MoveUpArray( int* P, int size);
void LEDArray_MoveDownArray( int* P, int size);
void LEDArray_MoveLeftArray( int* P, int size);
void LEDArray_MoveUpLeftArray( int* P, int size);
void LEDArray_MoveUpRightArray( int* P, int size);
void LEDArray_MoveDownRightArray( int* P, int size);
void LEDArray_MoveDownLeftArray( int* P, int size);
unsigned short LEDArray_Reverse16Bit( unsigned short num);
void LEDArray_Reset();



bool LEDArray_isOn(int num);
bool LEDArray_isOutOfBounds( int num );

//***********************************************************


void LEDArray_Reset(){
	for ( int i=0; i<COLS*ROWS; i++){
		LED_Lights[i]->isOn = false;
	}
}

unsigned short LEDArray_Reverse16Bit( unsigned short num){
	unsigned short tempNum = 0x0000;;
	
	for ( int i=0; i<16; i++){
		tempNum = SetBit( num, 16-i, GetBit(num,i) );
	}
	
	return tempNum;
}

void LEDArray_TurnOffLED( int num ){
	if ( LEDArray_isOutOfBounds(num)==true){return;}
	
	LED_Lights[num-1]->isOn = false;
	LED_Lights[num-1]->LEDcolor = Green;
}


void LEDArray_TurnOffArray(int *P, int size){
	for ( int i=0; i<size; i++){
		LEDArray_TurnOffLED(P[i]);
	}
}



void LEDArray_Init(){
	for (int i=0; i<sizeof_LED_Lights ; i++){
		LED_Lights[i] = (LED_Light*)malloc( sizeof(LED_Light) );
		
		
		LED_Lights[i]->number = i+1;
		LED_Lights[i]->isOn = false;
		LED_Lights[i]->LEDcolor = Green;
		LED_Lights[i]->isBlinking = false;
	}
}

void LEDArray_LightLED( int num,color col ){
	if ( LEDArray_isOutOfBounds(num)==true){return;}
	
	LED_Lights[num-1]->isOn = true;
	LED_Lights[num-1]->LEDcolor = col;
}



bool LEDArray_isOn(int num){
	
	if ( LEDArray_isOutOfBounds(num) == true ){ return false;}
	
	return LED_Lights[num-1]->isOn;
}



bool LEDArray_isOutOfBounds( int num ){
	if ( num < 1 ||  (num>ROWS*COLS) ){ return true;}
	
	
	return false;
}


void LEDArray_LightArrayMatrix(){
	
	for (int j=0,p=0; j<ROWS; j++,p += COLS){
		unsigned short colDataGreen = 0xFFFF;
		unsigned short colDataBlue = 0xFFFF;
		unsigned short colDataRed = 0xFFFF;
		for ( int i=p; i<COLS*(j+1); i++){
			if ( LED_Lights[i]->isOn == true ){
				if ( LED_Lights[i]->LEDcolor == Green){colDataGreen = SetBit16(colDataGreen,i-j*COLS,0);}
				if ( LED_Lights[i]->LEDcolor == Blue){colDataBlue = SetBit16(colDataBlue,i-j*COLS,0);}
				if ( LED_Lights[i]->LEDcolor == Red){colDataRed = SetBit16(colDataRed,i-j*COLS,0);}
				if ( LED_Lights[i]->LEDcolor == Teal){colDataGreen = SetBit16(colDataGreen,i-j*COLS,0);
													  colDataBlue = SetBit16(colDataBlue,i-j*COLS,0);}
				if ( LED_Lights[i]->LEDcolor == Yellow){ colDataGreen = SetBit16(colDataGreen,i-j*COLS,0);
														 colDataRed = SetBit16(colDataRed,i-j*COLS,0);}
				if ( LED_Lights[i]->LEDcolor == Purple){ colDataBlue = SetBit16(colDataBlue,i-j*COLS,0);
														 colDataRed = SetBit16(colDataRed,i-j*COLS,0);}
				if ( LED_Lights[i]->LEDcolor == White){ colDataBlue = SetBit16(colDataBlue,i-j*COLS,0);
														colDataRed = SetBit16(colDataRed,i-j*COLS,0);
														colDataGreen = SetBit16(colDataGreen,i-j*COLS,0);}
			}
		}
		
		
		
		//unsigned long data = (( unsigned long )colDataGreen) << 16 | (unsigned long)colDataBlue;
		//transmit_dataMain(data);
		/*transmit_dataBlue(colDataBlue);
		transmit_dataD(colDataGreen);*/
		transmit_dataRowsbot(0x00);
		transmit_dataGreen(colDataGreen);
		transmit_dataRed(colDataRed);
		transmit_dataBlue(colDataBlue);
		transmit_dataRowsbot(0x01 << j);
	}
	
	transmit_dataRowsbot(0x00);
}

void LEDArray_LightArray(int *P, int size, color col){
	for ( int i=0; i<size; i++){
		LEDArray_LightLED(P[i],col);
	}
}

void LEDArray_MoveUpArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] -= COLS;
	}
}


void LEDArray_MoveDownArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] += COLS;
	}
}



void LEDArray_MoveRightArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] += 1;
	}
}

void LEDArray_MoveLeftArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] -= 1;
	}
}

void LEDArray_MoveUpLeftArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] = P[i] - 1 -COLS;
	}
}


void LEDArray_MoveUpRightArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] += 1-COLS;
	}
}


void LEDArray_MoveDownRightArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] += 1+COLS;
	}
}

void LEDArray_MoveDownLeftArray( int *P, int size){
	
	LEDArray_TurnOffArray(P,size);
	
	for( int i=0; i < size; i++){
		P[i] = P[i]-1+COLS;
	}
}

#endif