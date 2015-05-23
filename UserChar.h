



/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */









#ifndef __USER_CHAR_H__
#define __USER_CHAR_H__

#include "bool.h"
#include "LEDArray.h"
#include "UserBullets.h"

//PRIVATE DATA
int UserChar_Array[4] = {100,116,117,115};
unsigned int sizeof_UserChar = sizeof(UserChar_Array) / sizeof(*UserChar_Array);
bool UserChar_isFlashing = false;
int UserChar_flashingCount = 0;
bool UserChar_isOn = true;
int UserChar_life = 5;
bool UserChar_isDead = false;
int UserChar_score = 0;
bool POWERUP_BLUE = false;
bool POWERUP_GREEN = false;
color UserChar_color = Green;
int rate_UserBullets = 10;

//PRIVATE HELPER FUNCTIONS
bool UserChar_isTop();//checks to see if any of the UserChar array elements is at the very top
bool UserChar_isBot();//^^
bool UserChar_isLeft();//^^
bool UserChar_isRight();//^^
void UserChar_loseLife(int num);


//PUBLIC FUNCTIONS
void UserChar_MoveUp();//moves the character Up, if it doesnt go out of limits
void UserChar_MoveDown();//^^
void UserChar_MoveLeft();//^^
void UserChar_MoveRight();//^^
void UserChar_MoveUpRight();//^^
void UserChar_MoveUpLeft();//^^
void UserChar_MoveDownRight();//^^
void UserChar_MoveDownLeft();//^^
void UserChar_ShootBullet();
void UserChar_Light();
void UserChar_checkForDeath();
void UserChar_requestFlashing(int num);
void UserChar_Reset();




//*********************************************************************************

void UserChar_Reset(){
	LEDArray_TurnOffArray(UserChar_Array,sizeof_UserChar);
	
	UserChar_Array[0] = 100;
	UserChar_Array[1] = 116;
	UserChar_Array[2] = 117;
	UserChar_Array[3] = 115;
	
}
void UserChar_requestFlashing(int num){
	if ( UserChar_isFlashing == false){
		UserChar_isFlashing = true;
		UserChar_flashingCount = (num%2 == 0) ? num+1: num;
	}
}

void UserChar_checkForDeath(){
	if ( UserChar_life <= 0){ UserChar_isDead = true;}
}

void UserChar_loseLife(int num){
	UserChar_life -= num;
}

void UserChar_ShootBullet(){
	UserBullet_MakeNew(UserChar_Array[0]-COLS);
}

bool UserChar_isTop(){
	for ( int i=0; i < sizeof_UserChar; i++){
		if ( UserChar_Array[i] <= COLS) {return true;}
	}
	
	return false;
}

bool UserChar_isBot(){
	for ( int i=0; i<sizeof_UserChar; i++){
		if ( UserChar_Array[i] > COLS*(ROWS-1) ){return true;}
	}
	
	return false;
}


bool UserChar_isLeft(){
	for ( int i=0; i < sizeof_UserChar; i++){
		if ( (UserChar_Array[i]-1) % COLS == 0){return true;}
	}
	
	return false;
}


bool UserChar_isRight(){
	for ( int i=0; i < sizeof_UserChar; i++){
		if ( UserChar_Array[i] % COLS == 0){return true;}
	}
	
	return false;
}



void UserChar_MoveUp(){
	if ( UserChar_isTop() == true ){return;}
		
	LEDArray_MoveUpArray(UserChar_Array,sizeof_UserChar);
}

void UserChar_MoveDown(){
	if ( UserChar_isBot() == true ){return;}
	
	LEDArray_MoveDownArray(UserChar_Array,sizeof_UserChar);
}


void UserChar_MoveLeft(){
	if ( UserChar_isLeft() == true ){return;}
	
	LEDArray_MoveLeftArray(UserChar_Array,sizeof_UserChar);
}

void UserChar_MoveRight(){
	if ( UserChar_isRight() == true ){return;}
	
	LEDArray_MoveRightArray(UserChar_Array,sizeof_UserChar);
}

void UserChar_MoveUpRight(){
	if ( UserChar_isRight() == true){return;}
	if ( UserChar_isTop() == true ){return;}
		
	LEDArray_MoveUpRightArray(UserChar_Array,sizeof_UserChar);	
}


void UserChar_MoveUpLeft(){
	if ( UserChar_isLeft() == true){return;}
	if ( UserChar_isTop() == true ){return;}
	
	LEDArray_MoveUpLeftArray(UserChar_Array,sizeof_UserChar);
}


void UserChar_MoveDownRight(){
	if ( UserChar_isRight() == true){return;}
	if ( UserChar_isBot() == true ){return;}
	
	LEDArray_MoveDownRightArray(UserChar_Array,sizeof_UserChar);
}


void UserChar_MoveDownLeft(){
	if ( UserChar_isLeft() == true){return;}
	if ( UserChar_isBot() == true ){return;}
	
	LEDArray_MoveDownLeftArray(UserChar_Array,sizeof_UserChar);
}

void UserChar_Light(){
	if ( UserChar_isOn == true){
		LEDArray_LightArray(UserChar_Array, sizeof_UserChar,UserChar_color);
	}else{
		LEDArray_TurnOffArray(UserChar_Array,sizeof_UserChar);
	}
}
#endif