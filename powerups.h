/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "colors.h"
#include "UserChar.h"
#include "Enemies.h"
#include "bool.h"
#include "ArrayManip.h"

typedef struct Powerup{
	color PowerColor;
	int position;
	int Powertimer;
	}Powerup;

Powerup* Powerups[10] = {0};
int sizeof_Powerups = sizeof(Powerups) / sizeof(*Powerups);

void Powerups_CreateNewBlue();//
void Powerups_CreateNewGreen();//
void Powerups_CreateNewRandom();//global
bool Powerups_doesUserCharHitPowerup(Powerup* Pow);//
void Powerups_giveUserPowerups();//global
void Powerups_Light();//global
void Powerups_Reset();//global
int Powerups_getRandomLocation();//
void Powerups_clearOutOfTime();//global
void Powerups_reduceTime();//global


void Powerups_reduceTime(){
	for ( int i=0; i< sizeof_Powerups; i++){
		if ( Powerups[i] != 0 ){
			Powerups[i]->Powertimer -= 1;
		}
	}
}

void Powerups_giveUserPowerups(){
	for ( int i=0; i<sizeof_Powerups; i++){
		if( Powerups[i] != 0 && Powerups_doesUserCharHitPowerup(Powerups[i])==true){
			if ( Powerups[i]->PowerColor == Blue ){ POWERUP_BLUE = true;}
			else if ( Powerups[i]->PowerColor == Green){ POWERUP_GREEN = true;}
				
			LEDArray_TurnOffLED(Powerups[i]->position);
			free(Powerups[i]);
			Powerups[i] = 0;
		}
	}
}

bool Powerups_doesUserCharHitPowerup(Powerup* Pow){
	return ArrayManip_isNumIn(UserChar_Array,sizeof_UserChar,Pow->position);
}

void Powerups_clearOutOfTime(){
	for ( int i=0; i<sizeof_Powerups; i++){
		if ( Powerups[i] != 0){
			if ( Powerups[i]->Powertimer <= 0){
				LEDArray_TurnOffLED(Powerups[i]->position);
				free(Powerups[i]);
				Powerups[i] = 0;
			}
		}
	}
}


void Powerups_CreateNewRandom(){
	if ( rand() % 2 == 0){ Powerups_CreateNewBlue();}
	else{ Powerups_CreateNewGreen();}
}


void Powerups_CreateNewBlue(){
	for ( int i=0; i<sizeof_Powerups; i++){
		if ( Powerups[i] == 0){
			Powerups[i] = (Powerup*)malloc( sizeof( Powerup ));
			
			Powerups[i]->position = Powerups_getRandomLocation();
			Powerups[i]->PowerColor = Blue;
			Powerups[i]->Powertimer = 10;
			return;
		}
	}
}

void Powerups_CreateNewGreen(){
	for ( int i=0; i<sizeof_Powerups; i++){
		if ( Powerups[i] == 0){
			Powerups[i] = (Powerup*)malloc( sizeof( Powerup ));
			
			Powerups[i]->position = Powerups_getRandomLocation();
			Powerups[i]->PowerColor = Green;
			Powerups[i]->Powertimer = 10;
			return;
		}
	}
}

int Powerups_getRandomLocation(){
	return 1 + rand()%128;
}

void Powerups_Light(){
	for ( int i=0; i<sizeof_Powerups; i++){
		if ( Powerups[i] != 0 ){
			LEDArray_LightLED(Powerups[i]->position,Powerups[i]->PowerColor);
		}
	}
}

void Powerups_Reset(){
	for ( int i=0; i<sizeof_Powerups; i++){
		if ( Powerups[i] != 0){
			LEDArray_TurnOffLED(Powerups[i]->position);
			free( Powerups[i]);
			Powerups[i] = 0;
		}
	}
}

#endif