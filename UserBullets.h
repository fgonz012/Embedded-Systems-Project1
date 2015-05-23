/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#ifndef __USER_BULLETS_H__
#define __USER_BULLETS_H__

#include "colors.h"

typedef struct UserBullet{
	
	int Position;
	color BulletColor;
	int dmg;
	
}UserBullet;

UserBullet* UserBullets[50]={0};
int sizeof_UserBullets_Array = sizeof(UserBullets) / sizeof(*UserBullets);


//PUBLIC
void UserBullet_MakeNew(int position);//make new bullet at position
void UserBullets_Move();//move all user bullets up 1
void UserBullets_Light();//Lights the UserBullets
void UserBullets_ClearOutOfBoundsBullets();
void UserBullets_Reset();



void UserBullets_Reset(){
	for ( int i=0; i<sizeof_UserBullets_Array; i++){
		if ( UserBullets[i] != 0){
			LEDArray_TurnOffLED(UserBullets[i]->Position);
			free( UserBullets[i]);
			UserBullets[i] = 0;
		}
	}
}


void UserBullets_ClearOutOfBoundsBullets(){
	for ( int i=0; i<sizeof_UserBullets_Array; i++){
		if ( UserBullets[i]->Position < 1){
			LEDArray_TurnOffLED(UserBullets[i]->Position);
			free(UserBullets[i]);
			UserBullets[i] = 0;
		}
	}
}

void UserBullet_MakeNew(int position){
	int index = 0;
	for (int i=0; i< sizeof_UserBullets_Array; i++){
		if ( UserBullets[i] == 0 ){
			UserBullets[i] = (UserBullet*)malloc(sizeof(UserBullet));
			index = i;
			break;
		}
	}
	
	UserBullets[index]->Position = position;
	UserBullets[index]->BulletColor = Teal;
	UserBullets[index]->dmg = 1;
	
}



void UserBullets_Move(){
	for (int i=0; i<sizeof_UserBullets_Array; i++){
		if( UserBullets[i] != 0 ){
			LEDArray_TurnOffLED(UserBullets[i]->Position);
			UserBullets[i]->Position -= COLS;
		}
	}
}



void UserBullets_Light(){
	for (int i=0; i<sizeof_UserBullets_Array; i++){
		if( UserBullets[i] != 0 ){
			LEDArray_LightLED(UserBullets[i]->Position,Teal);
		}
	}
}
#endif
