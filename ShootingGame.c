/*
 * ShootingGame Main Code
 *
 * Created: 5/13/2014 2:26:59 PM
 *  Author: Francisco
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "bit.h"
#include "LEDArray.h"
#include "scheduler.h"
#include "UserBullets.h"
#include "timer.h"
#include "UserChar.h"
#include <stdlib.h>
#include "Enemies.h"
#include "io.c"
#include "powerups.h"
unsigned char tempA = 0x00;
unsigned char Up = 0x00;
unsigned char Down = 0x00;
unsigned char Left = 0x00;
unsigned char Right = 0x00;
unsigned long int GCD = 1;
unsigned short tempADC = 0x0000;

//RATES*************************************************
unsigned int rate_UserChar_Up = 1;
unsigned int rate_UserChar_Down = 1;
unsigned int rate_UserChar_Left = 1;
unsigned int rate_UserChar_Right = 1;

unsigned int rate_Enemy1creation = 600;
unsigned int rate_Enemy2creation = 400;
unsigned int rate_Enemy1movement = 200;
unsigned int rate_Enemy2movement = 30;

//END_RATES**********************************************

//CONTROL VARIABLES**************************************

bool PAUSE = true;
bool RESET = false;



//END CONTROL VARIABLES**********************************


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


//STATE MACHINES
enum SM1_states {SM1_init} SM1_state;

int SMtick1(int state){//Lights LED matrix
	
	switch( state ){
		case SM1_init:
			state = SM1_init;
		break;
	}
	
	switch( state ){
		case SM1_init:
			LEDArray_LightArrayMatrix();
		break;
	}
	
	return state;
}




enum SM2_states { SM2_Action } SM2_state;
	
int SMtick2( int state){//continously outputs everything to LEDmatrix
	
	switch(state){
		case SM2_Action:
			state = SM2_Action;
		break;
	}
	
	
	switch(state){
		case SM2_Action:
			UserChar_Light();
			UserBullets_Light();
			Enemies_Light();
			Powerups_Light();
			//EnemyBullet_Light();
		break;
	}
	return state;
}



enum SM3_states { SM3_Wait, SM3_Up } SM3_state;

int SMtick3( int state ){//Moves UserChar up only
	
	static int i = 0;
	unsigned int UpOnly = Up && !Down && !Left && !Right;
	
	switch(state){
		case SM3_Wait:
			if ( UpOnly ){state = SM3_Up; UserChar_MoveUp();}
			else if ( !UpOnly ){state = SM3_Wait;}
		break;
		case SM3_Up:
			if ( UpOnly && i<rate_UserChar_Up ){state = SM3_Up;i++;}
			else if ( UpOnly && !(i<rate_UserChar_Up)  ){state = SM3_Up; UserChar_MoveUp(); i=0;}
			else if ( !UpOnly ){state = SM3_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM3_Wait:
			i=0;
		break;
		case SM3_Up:
		break;
	}
	
	return state;
}



enum SM4_states { SM4_Wait, SM4_Down } SM4_state;

int SMtick4( int state ){//Moves UserChar down only
	
	static int i = 0;
	unsigned char DownOnly = !Up && !Left && !Right && Down;
	
	switch(state){
		case SM4_Wait:
		if ( DownOnly ){state = SM4_Down; UserChar_MoveDown();}
		else if ( !DownOnly ){state = SM4_Wait;}
		break;
		case SM4_Down:
		if ( DownOnly && i<rate_UserChar_Down ){state = SM4_Down;i++;}
		else if ( DownOnly && !(i<rate_UserChar_Down)  ){state = SM4_Down; UserChar_MoveDown(); i=0;}
		else if ( !DownOnly ){state = SM4_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM4_Wait:
		i=0;
		break;
		case SM4_Down:
		break;
	}
	
	return state;
}




enum SM5_states { SM5_Wait, SM5_Right } SM5_state;

int SMtick5( int state ){//Moves UserChar right
	
	static int i = 0;
	unsigned char RightOnly = !Up && !Left && !Down && Right;
	
	switch(state){
		case SM5_Wait:
		if ( RightOnly ){state = SM5_Right; UserChar_MoveRight();}
		else if ( !RightOnly ){state = SM5_Wait;}
		break;
		case SM5_Right:
		if ( RightOnly && i<rate_UserChar_Right ){state = SM5_Right;i++;}
		else if ( RightOnly && !(i<rate_UserChar_Right)  ){state = SM5_Right; UserChar_MoveRight(); i=0;}
		else if ( !RightOnly ){state = SM5_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM4_Wait:
		i=0;
		break;
		case SM5_Right:
		break;
	}
	
	return state;
}



enum SM6_states { SM6_Wait, SM6_Left } SM6_state;

int SMtick6( int state ){//Moves UserChar Left
	
	static int i = 0;
	unsigned char LeftOnly = Left && !Down && !Up && !Right;
	
	switch(state){
		case SM6_Wait:
		if ( LeftOnly ){state = SM6_Left; UserChar_MoveLeft();}
		else if ( !LeftOnly ){state = SM6_Wait;}
		break;
		case SM6_Left:
		if ( LeftOnly && i<rate_UserChar_Left ){state = SM6_Left;i++;}
		else if ( LeftOnly && !(i<rate_UserChar_Left)  ){state = SM6_Left; UserChar_MoveLeft(); i=0;}
		else if ( !LeftOnly ){state = SM6_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM6_Wait:
		i=0;
		break;
		case SM6_Left:
		break;
	}
	
	return state;
}





enum SM7_states { SM7_Wait, SM7_Left } SM7_state;

int SMtick7( int state ){//Moves UserChar UpLeft
	
	static int i = 0;
	unsigned char UpLeftOnly = Left && !Down && Up && !Right;
	
	switch(state){
		case SM7_Wait:
		if ( UpLeftOnly ){state = SM7_Left; UserChar_MoveUpLeft();}
		else if ( !UpLeftOnly ){state = SM7_Wait;}
		break;
		case SM7_Left:
		if ( UpLeftOnly && i<rate_UserChar_Left ){state = SM7_Left;i++;}
		else if ( UpLeftOnly && !(i<rate_UserChar_Left)  ){state = SM7_Left; UserChar_MoveUpLeft(); i=0;}
		else if ( !UpLeftOnly ){state = SM7_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM7_Wait:
		i=0;
		break;
		case SM7_Left:
		break;
	}
	
	return state;
}




enum SM8_states { SM8_Wait, SM8_DownLeft } SM8_state;

int SMtick8( int state ){//Moves UserChar DownLeft
	
	static int i = 0;//***
	unsigned char DownLeftOnly = Left && Down && !Up && !Right;
	
	switch(state){
		case SM8_Wait:
		if ( DownLeftOnly ){state = SM8_DownLeft;}
		else if ( !DownLeftOnly ){state = SM8_Wait;}
		break;
		case SM8_DownLeft:
		if ( DownLeftOnly && i<rate_UserChar_Left ){state = SM8_DownLeft;i++;}
		else if ( DownLeftOnly && !(i<rate_UserChar_Left)  ){state = SM8_DownLeft; UserChar_MoveDownLeft(); i=0;}
		else if ( !DownLeftOnly ){state = SM8_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM8_Wait:
		i=0;
		break;
		case SM8_DownLeft:
		break;
	}
	
	return state;
}





enum SM9_states { SM9_Wait, SM9_UpRight } SM9_state;

int SMtick9( int state ){//Moves UserChar UpRight
	
	static int i = 0;//********
	unsigned char UpRightOnly = !Left && !Down && Up && Right;
	
	switch(state){
		case SM9_Wait:
		if ( UpRightOnly ){state = SM9_UpRight; UserChar_MoveUpRight();}
		else if ( !UpRightOnly ){state = SM9_Wait;}
		break;
		case SM9_UpRight:
		if ( UpRightOnly && i<rate_UserChar_Left ){state = SM9_UpRight;i++;}
		else if ( UpRightOnly && !(i<rate_UserChar_Left)  ){state = SM9_UpRight; UserChar_MoveUpRight(); i=0;}
		else if ( !UpRightOnly ){state = SM9_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM9_Wait:
		i=0;
		break;
		case SM9_UpRight:
		break;
	}
	
	return state;
}



enum SM10_states { SM10_Wait, SM10_UpLeft } SM10_state;

int SMtick10( int state ){//Moves UserChar UpLeft
	
	static int i = 0;//********
	unsigned char UpLeftOnly = !Left && Down && !Up && Right;
	
	switch(state){
		case SM10_Wait:
		if ( UpLeftOnly ){state = SM10_UpLeft; UserChar_MoveDownRight();}
		else if ( !UpLeftOnly ){state = SM10_Wait;}
		break;
		case SM10_UpLeft:
		if ( UpLeftOnly && i<rate_UserChar_Left ){state = SM10_UpLeft;i++;}
		else if ( UpLeftOnly && !(i<rate_UserChar_Left)  ){state = SM10_UpLeft; UserChar_MoveDownRight(); i=0;}
		else if ( !UpLeftOnly ){state = SM10_Wait;}
		break;
	}
	
	
	
	switch(state){
		case SM10_Wait:
		i=0;
		break;
		case SM10_UpLeft:
		break;
	}
	
	return state;
}


enum SM8_States {SM11_Wait, SM11_Shoot } SM11_State;

int SMtick11( int state ){
	
	static int i=0;
	int i_max = rate_UserBullets;
	
	unsigned char Shoot = !GetBit(PINA,2);
	
	switch(state){
		case SM11_Shoot:
		if ( Shoot && (i<i_max) ){state = SM11_Shoot; i++;}
		else if (Shoot && !(i<i_max) ){state = SM11_Shoot; UserChar_ShootBullet();i=0;}
		else if ( !Shoot ){state = SM11_Wait;}
		break;
		case SM11_Wait:
		if ( Shoot ){ state = SM11_Shoot; UserChar_ShootBullet(); /*EnemyBullet_fireBulletsForAllEnemies()*/;}
		else if ( !Shoot ){ state = SM11_Wait;}
		break;
	}
	
	switch(state){
		case SM11_Shoot:
		break;
		case SM11_Wait:
		i=0;
		break;
	}
	
	return state;
}


enum SM12_States { SM12_MoveBullets } SM12_State;

int SMtick12( int state ){//moves the bullets; change rate at the top
	
	static int i=0;
	int i_max = 1;
	switch(state){
		case SM12_MoveBullets:
		if(i<i_max){state = SM12_MoveBullets; i++;}
		else if ( !(i<i_max) ){
			state = SM12_MoveBullets;
			UserBullets_Move();
			i=0;
		}
		break;
	}
	
	
	switch(state){
		case SM12_MoveBullets:
		break;
	}
	
	return state;
}



enum SM13_states {SM13_CalculatePaths} SM13_state;

int SMtick13( int state ){
	
	switch(state){
		case SM13_CalculatePaths:
		state = SM13_CalculatePaths;
		break;
	}
	
	
	switch(state){
		case SM13_CalculatePaths:
			Enemies_calculatePaths();
			Enemies_clearDeadEnemies();
			UserBullets_ClearOutOfBoundsBullets();
			Enemies_loseLivesToAllHitEnemies();
			Enemies_checkForHitOnUserChar();
			UserChar_checkForDeath();
			Enemies_clearOutOfBoundsEnemies();
			Powerups_giveUserPowerups();
			Powerups_clearOutOfTime();
		break;
	}
	
	return state;
}


enum SM14_states {SM14_MoveEnemies} SM14_state;

int SMtick14( int state ){
	
	switch(state){
		case SM14_MoveEnemies:
		state = SM14_MoveEnemies;
		break;
	}
	
	
	
	
	switch(state){
		case SM14_MoveEnemies:
			Enemies_move();
		break;
	}
	
	return state;
}


enum SM15_states { SM15_Init, SM15_CreateEnemies } SM15_state;

int SMtick15( int state){//creates enemies of type1
	
	
	switch(state){
		case SM15_CreateEnemies:
			state = SM15_CreateEnemies;
		break;
	}
	
	
	switch(state){
		case SM15_CreateEnemies:
			Enemies_createNew1();
		break;
	}
	return state;
}


enum SM16_states { SM16_NoBlink, SM16_Blinking } SM16_state;
	
int SMtick16(int state){
	
	static int i=0;
	
	switch(state){
		case SM16_NoBlink:
			if ( UserChar_isFlashing == false ){ state = SM16_NoBlink;}
			else if (UserChar_isFlashing == true){ state = SM16_Blinking;}
		break;
		case SM16_Blinking:
			if (i<UserChar_flashingCount){state = SM16_Blinking;i++;}
			else if (!(i<UserChar_flashingCount)){state = SM16_NoBlink;i=0;UserChar_isFlashing=false;UserChar_flashingCount=0;}
		break;
	}
	
	
	
	switch(state){
		case SM16_NoBlink:
			i=0;
		break;
		case SM16_Blinking:
			if ( UserChar_isOn == true ){UserChar_isOn = false;}
			else {UserChar_isOn = true;}
		break;
	}
	return state;
}



enum SM17_states { SM17_MoveEnemyBullets } SM17_state;
	
int SMtick17 (int state){
	switch(state){
		case SM17_MoveEnemyBullets:
			state = SM17_MoveEnemyBullets;
		break;
	}
	
	switch(state){
		case SM17_MoveEnemyBullets:
			//EnemyBullet_MoveAllBullets();
		break;
	}
	
	return state;
}

enum SM18_states { SM18_GETy, SM18_GETx } SM18_state;
	
int SMtick18( int state ){
	switch(state){
		case SM18_GETx:
			state = SM18_GETy;
		break;
		case SM18_GETy:
			state = SM18_GETx;
		break;
	}
	
	switch(state){
		case SM18_GETx:
			ADMUX &= 0xE0;
			tempADC = ADC;
			
			if ( tempADC < 200 ){Right=1;}
			else if ( tempADC > 800 ){ Left=1;}
			else { Left = 0; Right=0;}
		break;
		case SM18_GETy:
			ADMUX |= 0x01;
			tempADC = ADC;
			
			
			if ( tempADC <200 ){ Up = 1;}
			else if ( tempADC > 800 ){Down =1;}
			else { Up = 0; Down = 0;}
		break;
	}
	
	return state;
	
}

enum SM19_states { SM19_CreateEnemies2 } SM19_state;
int SMtick19( int state){//creates enemies of type1
	
	
	switch(state){
		case SM19_CreateEnemies2:
		state = SM19_CreateEnemies2;
		break;
	}
	
	
	switch(state){
		case SM19_CreateEnemies2:
			Enemies_createNew2();
		break;
	}
	return state;
}


enum SM20_states {SM20_MoveEnemies} SM20_state;

int SMtick20( int state ){//move type 2 enemies
	
	switch(state){
		case SM20_MoveEnemies:
		state = SM20_MoveEnemies;
		break;
	}
	
	
	
	
	switch(state){
		case SM20_MoveEnemies:
			Enemies_move2();
		break;
	}
	
	return state;
}


enum SM21_states { SM21_Init, SM21_MoveCursor, SM21_DisplayLife, SM21_MoveCursorScore, SM21_DisplayHundred, SM21_DisplayTens, SM21_DisplayOnes } SM21_state;

int SMtick21( int state ){//Display scores/life
	
	static int tempScore = 10;
	static int tempLife = 0;
	
	//if (  tempScore == UserChar_score && tempLife == UserChar_life ){return state;}
	
	int Hundreds = UserChar_score / 100;
	int Tens = (UserChar_score % 100) / 10;
	int Ones = (UserChar_score % 100) % 10;
	
	switch(state){
		
		case SM21_Init:
			state = SM21_MoveCursor;
		break;
		
		case SM21_MoveCursor:
			state = SM21_DisplayLife;
		break;
		
		case SM21_DisplayLife:
			state = SM21_MoveCursorScore;
		break;
		
		case SM21_MoveCursorScore:
			state = SM21_DisplayHundred;
		break;
		
		case SM21_DisplayHundred:
			state = SM21_DisplayTens;
		break;
		
		case SM21_DisplayTens:
			state = SM21_DisplayOnes;
		break;
		
		case SM21_DisplayOnes:
			state = SM21_MoveCursor;
		break;
	}
	
	
	
	
	switch(state){
		
		case SM21_Init:
		break;
		
		case SM21_MoveCursor:
			LCD_CursorSynch(7);
		break;
		
		case SM21_DisplayLife:
			LCD_WriteDataSynch(UserChar_life + '0');
		break;
		
		case SM21_MoveCursorScore:
			LCD_CursorSynch(23);
		break;
		
		case SM21_DisplayHundred:
			LCD_WriteDataSynch(Hundreds + '0');
		break;
		
		case SM21_DisplayTens:
			LCD_WriteDataSynch(Tens+'0');
		break;
		
		case SM21_DisplayOnes:
			LCD_WriteDataSynch(Ones+'0');
		break;
	}
	
	return state;
}

enum SM22_states { SM22_NotPaused, SM22_Paused } SM22_state;
	
int SMtick22( int state ){
	
	static int i=0;
	int timeHeld = 10;
	
	int HeldButton = !GetBit(PINA,2);
	
	switch(state){
		case SM22_NotPaused:
			if ( PAUSE == true ){ state = SM22_Paused;}
			else if ( PAUSE == false ){ state = SM22_NotPaused;}
		break;
		
		case SM22_Paused:
			if ( HeldButton && i < timeHeld ){state = SM22_Paused; i++;}
			else if ( !HeldButton && i < timeHeld ){state = SM22_Paused; i=0;}
			else if ( HeldButton && !(i < timeHeld)){ state = SM22_NotPaused; i=0; RESET = true; PAUSE = false;}
		break;
	}
	
	
	
	switch(state){
		case SM22_NotPaused:
		break;
		case SM22_Paused:
		break;
	}
	
	return state;
}

enum SM23_states { SM23_CreateNewPowerup } SM23_state;
	
int SMtick23( int state){
	
	switch(state){
		case SM23_CreateNewPowerup:
			state = SM23_CreateNewPowerup;
		break;
	}
	
	
	switch(state){
		case SM23_CreateNewPowerup:
			Powerups_CreateNewRandom();
		break;
	}
	
	
	return state;
}

enum SM24_states { SM24_PowerupsTimer } SM24_state;
	
int SMtick24( int state ){
	
	switch(state){
		case SM24_PowerupsTimer:
			state = SM24_PowerupsTimer;
		break;
	}
	
	switch(state){
		case SM24_PowerupsTimer:
			Powerups_reduceTime();
		break;
	}
	
	
	return state;
}

enum SM25_states { SM25_WaitBlue, SM25_StopTime } SM25_state;
	
int SMtick25( int state ){
	
	static int i=0;
	int i_max = 250;
	switch ( state ){
		case SM25_WaitBlue:
			if ( POWERUP_BLUE == true ){ state = SM25_StopTime;}
			else if ( POWERUP_BLUE == false){ state = SM25_WaitBlue;}
		break;
		
		case SM25_StopTime:
			if ( i<i_max ){ state = SM25_StopTime; i++;}
			else if ( !(i<i_max) ){ state = SM25_WaitBlue; i=0; POWERUP_BLUE = false; }
		break;
	}
	
	
	switch ( state ){
		case SM25_WaitBlue:
			i=0;
		break;
		
		case SM25_StopTime:
		break;
	}
	
	
	
	return state;
}


enum SM26_states { SM26_WaitGreen, SM26_QuickFire } SM26_state;

int SMtick26( int state ){
	
	static int i=0;
	int i_max = 250;
	switch ( state ){
		case SM26_WaitGreen:
		if ( POWERUP_GREEN == true ){ state = SM26_QuickFire; rate_UserBullets = 1;}
		else if ( POWERUP_GREEN == false){ state = SM26_WaitGreen;}
		break;
		
		case SM26_QuickFire:
		if ( i<i_max ){ state = SM26_QuickFire; i++;}
		else if ( !(i<i_max) ){ state = SM26_WaitGreen; i=0; POWERUP_GREEN = false; rate_UserBullets=10; }
		break;
	}
	
	
	switch ( state ){
		case SM26_WaitGreen:
		i=0;
		break;
		
		case SM26_QuickFire:
		break;
	}
	
	
	
	return state;
}
int main(void)
{
	DDRA = 0xF0; PORTA = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	LEDArray_Init();
	ADC_init();
	LCD_init();
	TimerOn();
	TimerSet(GCD);
	
	LCD_DisplayString(1,"Lives:          Score:");
	
	task tasks[26];
	const unsigned char numTasks = sizeof(tasks) / sizeof(*tasks);
	
	/* Have to:
		change the size of tasks array
		create the struct variables
		check GCD at the top
	
	
	*/
	
	
	tasks[0].period = 1;//controls the LED matrix array
	tasks[0].elapsedTime = tasks[0].period;
	tasks[0].TickFct = &SMtick1;
	tasks[0].state = SM1_init;
	
	tasks[1].period = 2;//Lights everything
	tasks[1].elapsedTime = tasks[1].period;
	tasks[1].TickFct = &SMtick2;
	tasks[1].state = SM2_Action;
	
	tasks[2].period = 5;//moves main character Up Only
	tasks[2].elapsedTime = tasks[2].period;
	tasks[2].TickFct = &SMtick3;
	tasks[2].state = SM3_Wait;
	
	tasks[3].period = 5;//moves main character Down Only
	tasks[3].elapsedTime = tasks[3].period;
	tasks[3].TickFct = &SMtick4;
	tasks[3].state = SM4_Wait;
	
	tasks[4].period = 5;//moves main character Right Only
	tasks[4].elapsedTime = tasks[4].period;
	tasks[4].TickFct = &SMtick5;
	tasks[4].state = SM5_Wait;
	
	tasks[5].period = 5;//moves main character Left Only
	tasks[5].elapsedTime = tasks[5].period;
	tasks[5].TickFct = &SMtick6;
	tasks[5].state = SM6_Wait;
	
	tasks[6].period = 5;//moves main character UpLeft Only
	tasks[6].elapsedTime = tasks[6].period;
	tasks[6].TickFct = &SMtick7;
	tasks[6].state = SM7_Wait;
	
	tasks[7].period = 5;//moves main character DownLeft Only
	tasks[7].elapsedTime = tasks[7].period;
	tasks[7].TickFct = &SMtick8;
	tasks[7].state = SM8_Wait;
	
	tasks[8].period = 5;//moves main character UpRight Only
	tasks[8].elapsedTime = tasks[8].period;
	tasks[8].TickFct = &SMtick9;
	tasks[8].state = SM9_Wait;
	
	tasks[9].period = 5;//moves main character UpLeft Only
	tasks[9].elapsedTime = tasks[9].period;
	tasks[9].TickFct = &SMtick10;
	tasks[9].state = SM10_Wait;
	
	tasks[10].period = 5;//ShootsBullets
	tasks[10].elapsedTime = tasks[10].period;
	tasks[10].TickFct = &SMtick11;
	tasks[10].state = SM11_Wait;
	
	tasks[11].period = 5;//MoveBullets
	tasks[11].elapsedTime = tasks[11].period;
	tasks[11].TickFct = &SMtick12;
	tasks[11].state = SM12_MoveBullets;
	
	tasks[12].period = 5;//CalculatePaths
	tasks[12].elapsedTime = tasks[12].period;
	tasks[12].TickFct = &SMtick13;
	tasks[12].state = SM13_CalculatePaths;
	
	tasks[13].period = rate_Enemy1movement;//move enemies type 1
	tasks[13].elapsedTime = 0;
	tasks[13].TickFct = &SMtick14;
	tasks[13].state = SM14_MoveEnemies;
	
	tasks[14].period = rate_Enemy1creation;//create enemies type 1
	tasks[14].elapsedTime = tasks[14].period;
	tasks[14].TickFct = &SMtick15;
	tasks[14].state = SM15_CreateEnemies;
	
	tasks[15].period = 10;//blink userChar
	tasks[15].elapsedTime = tasks[15].period;
	tasks[15].TickFct = &SMtick16;
	tasks[15].state = SM16_NoBlink;
	
	tasks[16].period = 200;//blink userChar
	tasks[16].elapsedTime = tasks[16].period;
	tasks[16].TickFct = &SMtick17;
	tasks[16].state = SM17_MoveEnemyBullets;
	
	tasks[17].period = 2;//get user control inputs
	tasks[17].elapsedTime = tasks[17].period;
	tasks[17].TickFct = &SMtick18;
	tasks[17].state = SM18_GETx;
	
	tasks[18].period = rate_Enemy2creation;//create enemies type 2
	tasks[18].elapsedTime = 0;
	tasks[18].TickFct = &SMtick19;
	tasks[18].state = SM19_CreateEnemies2;
	
	tasks[19].period = rate_Enemy2movement;//move enemies type 2
	tasks[19].elapsedTime = 0;
	tasks[19].TickFct = &SMtick20;
	tasks[19].state = SM20_MoveEnemies;
	
	tasks[20].period = 3;//display life/score
	tasks[20].elapsedTime = 0;
	tasks[20].TickFct = &SMtick21;
	tasks[20].state = SM21_Init;
	
	tasks[21].period = 50;//reset after death
	tasks[21].elapsedTime = 0;
	tasks[21].TickFct = &SMtick22;
	tasks[21].state = SM22_NotPaused;
	
	
	tasks[22].period = 3000;//creates powerups
	tasks[22].elapsedTime = 0;
	tasks[22].TickFct = &SMtick23;
	tasks[22].state = SM23_CreateNewPowerup;
	
	tasks[23].period = 100;//powerups timers
	tasks[23].elapsedTime = 0;
	tasks[23].TickFct = &SMtick24;
	tasks[23].state = SM24_PowerupsTimer;
	
	tasks[24].period = 2;//powerups timers
	tasks[24].elapsedTime = 0;
	tasks[24].TickFct = &SMtick25;
	tasks[24].state = SM25_WaitBlue;
	
	tasks[25].period = 2;//powerups timers
	tasks[25].elapsedTime = 0;
	tasks[25].TickFct = &SMtick26;
	tasks[25].state = SM26_WaitGreen;
	
	while(1){
		if ( UserChar_isDead == true){ PAUSE = true;}
			
		if (RESET == true){
							//LEDArray_Reset();
							UserChar_Reset();
							Enemies_Reset();
							UserBullets_Reset();
							Powerups_Reset();
							UserChar_life = 5;
							UserChar_score = 0;
							RESET = false;
							PAUSE = false;
							UserChar_isDead = false;}
			
		
		if ( POWERUP_BLUE == true ){ UserChar_color = Blue;}
		else if ( POWERUP_GREEN == true) { UserChar_color = White;}
		else { UserChar_color = Green;}
		
		unsigned int i = 0;
		for (i = 0; i < numTasks; i++) { // Heart of the scheduler code
			
			
			if (PAUSE == true){
				if ( i==2 || i == 3 || i==4 || i==5 || i==6 || i==7 || i==8 || i==9 || i==10 || i==11 || i==12 || i==13 || i==14 || i==15 || i==22 || i==23){continue;}
			}
			
			if ( POWERUP_BLUE == true ){ if ( i== 13 || i==14 || i==18 || i==19){continue;} }
			
			if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}
			tasks[i].elapsedTime += GCD;
		}
		while( !TimerFlag );
		TimerFlag = 0;
	}
}