/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "bool.h"
#include "ArrayManip.h"
#include "LEDArray.h"
#include <stdlib.h>
#include "UserBullets.h"



typedef struct EnemyBullet{
	
	int position;
	int dmg;
	color col;
	
}EnemyBullet;

typedef struct Enemy{
	
	unsigned int Lives;
	int Enemy_Position_Array[10];
	int Enemy_Front;
	int Enemy_Gun[10];
	int Enemy_Relative_Position_Array[10];
	int Next_Enemy_Position_Array[10];
	unsigned int Size_Of_Arrays;
	EnemyBullet* EnemyBullets[10];
	unsigned int sizeof_enemyBullets;
	unsigned int rateMovement;
	unsigned int typeOfEnemy;
	color EnemyColor;
}Enemy;


Enemy* Enemies[10] = {0};
unsigned int sizeof_Enemies_Array = sizeof(Enemies)/sizeof(*Enemies);


//PRIVATE**************************

int Enemies_getRandomNewFront(Enemy* En);//done
void Enemies_loseLife(Enemy* En, int dmg);
bool Enemies_doEnemiesCollide( Enemy* En1, Enemy* En2);
void Enemies_clearDeadEnemies();
void Enemies_clearOutOfBoundsEnemies();
int* Enemies_getRandomNewPath(Enemy* En);
bool Enemies_doesArrayCollideWithEnemies(int* P, int size, int index);
bool Enemies_isArrayValidBounds( int* P, int size);
bool Enemies_isArrayValid( int* P, int size, int index);
bool Enemies_doesArrayCollideWithEnemy( int* P, int size, Enemy* En);
void Enemies_makeNewFront(Enemy* En, int newFront);
bool Enemies_isHitByBullet( Enemy* En, UserBullet* Bul);
void Enemies_checkIsHitByAnyBullet( Enemy* En);
void Enemies_loseLivesToAllHitEnemies();
bool Enemies_doesEnemyHitUserChar(Enemy* En);
void EnemyBullet_fireBullet( Enemy* En);
void EnemyBullet_removeOutOfBoundsBullets( Enemy* En);
void EnemyBullet_moveBulletsForEnemy(Enemy* En);
void EnemyBullet_lightBulletsForSinglEnemy(Enemy* En);
int Enemies_getRandomNewFront2(Enemy* En);
void Enemies_move2();
int Enemies_getRandomEnemyStart();



//PUBLIC*****************************

void Enemies_move();
void Enemies_createNew1();
void Enemies_createNew2();
void Enemies_clearEnemies();
void Enemies_Light();
void Enemies_calculatePaths();
void Enemies_clearDeadEnemies();
void Enemies_checkForHitOnUserChar();
void EnemyBullet_MoveAllBullets();
void EnemyBullet_Light();
void Enemies_Reset();


void Enemies_Reset(){
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] != 0){
			LEDArray_TurnOffArray(Enemies[i]->Enemy_Position_Array, Enemies[i]->Size_Of_Arrays);
			free ( Enemies[i]);
			Enemies[i]=0;
		}
	}
}



int Enemies_getRandomEnemyStart(){
	return rand() % COLS + 1;		
}

int Enemies_getRandomEnemyStart2(){
	return (32 + rand() % COLS)*-1;
}

void Enemies_move2(){//moves type 1 enemies
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] !=0 && Enemies[i]->typeOfEnemy == 2){
			LEDArray_TurnOffArray(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays);
			ArrayManip_copy(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays,
			Enemies[i]->Next_Enemy_Position_Array);
			Enemies[i]->Enemy_Front = Enemies[i]->Enemy_Position_Array[0];
		}
	}
}



int Enemies_getRandomNewFront2(Enemy* En){
	int randNum = rand()%10;//*rand()%5;

	if(randNum == 0){return En->Enemy_Front -1;}//Left
	if(randNum == 1){return En->Enemy_Front +1;}//Right
	if(randNum == 2){return En->Enemy_Front +COLS;}//Down
	if(randNum == 3){return En->Enemy_Front +COLS + 1;}//Down and Right
	if(randNum == 4){return En->Enemy_Front +COLS - 1;}//Down and Left
	if(randNum == 5){return En->Enemy_Front +COLS;}//Down
	if(randNum == 6){return En->Enemy_Front +COLS;}//Down
	if(randNum == 7){return En->Enemy_Front +COLS;}//Down
	if(randNum == 8){return En->Enemy_Front +COLS;}//Down
	if(randNum == 9){return En->Enemy_Front +COLS;}//Down

	return 0;//shouldnt happen

}


void Enemies_createNew2(){
	
	int index = 0;
	for (int i=0; i<sizeof_Enemies_Array; i++){
		
		if (Enemies[i]==0){
			Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			index = i;
			break;
		}
		if ( i==sizeof_Enemies_Array-1){return;}
	}
	
	int randomFront = 0;
	
	Enemies[index] -> Enemy_Relative_Position_Array[0] = 0;
	Enemies[index] -> Enemy_Relative_Position_Array[1] = -1;
	
	Enemies[index] -> Size_Of_Arrays = 2;
	
	for ( int kl=0; kl<10; kl++){
		
		int tempArray[2] = {0};
		
		randomFront = Enemies_getRandomEnemyStart2();
		
		
		tempArray[0] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[0];
		tempArray[1] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[1];
		
		if ( Enemies_isArrayValid(tempArray,2,index) == true ){
			break;
		}
	}
	
	Enemies[index] -> Enemy_Front = randomFront;
	
	Enemies[index] ->Enemy_Position_Array[0] = Enemies[index]->Enemy_Relative_Position_Array[0] + randomFront;
	Enemies[index] ->Enemy_Position_Array[1] = Enemies[index]->Enemy_Relative_Position_Array[1] + randomFront;
	
	Enemies[index]->Next_Enemy_Position_Array[0] = Enemies[index]->Enemy_Position_Array[0] + COLS;
	Enemies[index]->Next_Enemy_Position_Array[1] = Enemies[index]->Enemy_Position_Array[1] + COLS;
	
	Enemies[index]->Lives = 1;
	Enemies[index]->sizeof_enemyBullets = 10;
	Enemies[index]->rateMovement = 200;
	Enemies[index]->typeOfEnemy = 2;
	Enemies[index]->EnemyColor = Purple;
	
	
	
}



void EnemyBullet_fireBulletsForAllEnemies(){
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] != 0){
			EnemyBullet_fireBullet(Enemies[i]);
		}
	}
}

void EnemyBullet_MoveAllBullets(){
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] != 0){
			EnemyBullet_moveBulletsForEnemy(Enemies[i]);
		}
	}
}
void EnemyBullet_moveBulletsForEnemy(Enemy* En){
	for ( int i=0; i<En->sizeof_enemyBullets; i++){
		if ( En->EnemyBullets[i] != 0){
			LEDArray_TurnOffLED(En->EnemyBullets[i]->position);
			En->EnemyBullets[i]->position += COLS;
		}
	}
}



void EnemyBullet_Light(){
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if (Enemies[i] != 0){
			EnemyBullet_lightBulletsForSinglEnemy(Enemies[i]);
		}
	}
}


void EnemyBullet_lightBulletsForSinglEnemy(Enemy* En){
	for ( int i=0; i <En->sizeof_enemyBullets; i++){
		if ( En->EnemyBullets[i] != 0){
			LEDArray_LightLED(En->EnemyBullets[i]->position, En->EnemyBullets[i]->col);
		}
	}
}

void EnemyBullet_fireBullet(Enemy* En){
	for ( int i=0 ; i <En->sizeof_enemyBullets; i++){
		if ( En->EnemyBullets[i] == 0){
			En->EnemyBullets[i] = (EnemyBullet*)malloc(sizeof(EnemyBullet));
			En->EnemyBullets[i]->position = Enemies[i]->Enemy_Front + COLS;
			En->EnemyBullets[i]->dmg = 1;
			En->EnemyBullets[i]->col = Blue;
			break;
		}
	}
}


bool Enemies_doesEnemyHitUserChar(Enemy* En){
	if ( ArrayManip_doShareNum(En->Enemy_Position_Array, En->Size_Of_Arrays, UserChar_Array,sizeof_UserChar)==true){
		return true;
	}
	return false;
}


void Enemies_checkForHitOnUserChar(){
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] != 0 && Enemies_doesEnemyHitUserChar(Enemies[i])==true){
			UserChar_loseLife(1);
			UserChar_requestFlashing(11);
			LEDArray_TurnOffArray(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays);
			free(Enemies[i]);
			Enemies[i]=0;
		}
	}
}


void Enemies_clearDeadEnemies(){
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] !=0 && Enemies[i]->Lives <= 0){
			if (Enemies[i]->typeOfEnemy == 1){ UserChar_score += 1;}
			if (Enemies[i]->typeOfEnemy == 2){ UserChar_score += 2;}
			LEDArray_TurnOffArray(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays);
			free(Enemies[i]);
			Enemies[i]=0;
			return;
		}
	}
}

void Enemies_loseLivesToAllHitEnemies(){
	for ( int i=0; i < sizeof_Enemies_Array; i++){
		Enemies_checkIsHitByAnyBullet(Enemies[i]);
	}
}


void Enemies_checkIsHitByAnyBullet( Enemy* En){
	for ( int i=0; i<sizeof_UserBullets_Array; i++){
		if ( (UserBullets[i] != 0) && Enemies_isHitByBullet(En,UserBullets[i])==true){
			Enemies_loseLife(En,UserBullets[i]->dmg);
			LEDArray_TurnOffLED(UserBullets[i]->Position);
			free(UserBullets[i]);
			UserBullets[i] = 0;
		}
	}
}

bool Enemies_isHitByBullet( Enemy* En, UserBullet* Bul){
	if ( ArrayManip_isNumIn(En->Enemy_Position_Array,En->Size_Of_Arrays,Bul->Position) == true){
		/*
		LEDArray_TurnOffLED(Bul->Position);
		free(Bul);
		Bul = 0;*/
		return true;
	}
	return false;
}

void Enemies_Light(){
	for (int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] !=0 ){
			LEDArray_LightArray(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays,Enemies[i]->EnemyColor);
		}
	}
}
void Enemies_calculatePaths(){
	
	for( int i=0; i<sizeof_Enemies_Array; i++){
		
		if( Enemies[i] !=0 && ArrayManip_areEqual(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays,Enemies[i]->Next_Enemy_Position_Array)==true){
			for( int j=0; j<10; j++){
				
				int tempFront = 0;
				if ( Enemies[i]->typeOfEnemy == 1 ){tempFront = Enemies_getRandomNewFront(Enemies[i]);}
				else if ( Enemies[i]->typeOfEnemy == 2){ tempFront = Enemies_getRandomNewFront2(Enemies[i]);}
				int* tempPath = (int*)malloc(Enemies[i]->Size_Of_Arrays*sizeof(int));
				
				for ( int kl=0; kl<Enemies[i]->Size_Of_Arrays; kl++){
					tempPath[kl] = Enemies[i]->Enemy_Relative_Position_Array[kl] + tempFront;
				}
				
				
			
				if ( Enemies_isArrayValid(tempPath,Enemies[i]->Size_Of_Arrays,i) == true ){
					ArrayManip_copy(Enemies[i]->Next_Enemy_Position_Array,Enemies[i]->Size_Of_Arrays,tempPath);
					free(tempPath);
					break;
				}
				free(tempPath);
			}
		}
		
	}
	
}


void Enemies_makeNewFront(Enemy* En, int newFront){
	En->Enemy_Front = newFront;
}

void Enemies_createNew1(){
	
	int index = 0;
	for (int i=0; i<sizeof_Enemies_Array; i++){
		
		if (Enemies[i]==0){
			Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			index = i;
			break;
		}
		if ( i==sizeof_Enemies_Array){return;}
	}
	
	Enemies[index] -> Enemy_Relative_Position_Array[0] = 0;
	Enemies[index] -> Enemy_Relative_Position_Array[1] = -1;
	Enemies[index] -> Enemy_Relative_Position_Array[2] = 1;
	Enemies[index] -> Enemy_Relative_Position_Array[3] = COLS;
	Enemies[index] -> Size_Of_Arrays = 4;
	
	
	int randomFront = 0;
	
	for ( int kl=0; kl<10; kl++){
	
		int tempArray[4] = {0};
			
		randomFront = Enemies_getRandomEnemyStart();
		
		if ( randomFront == 1 ){ randomFront += 1;}
		if ( randomFront == COLS ){ randomFront -= 1;}
		
		tempArray[0] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[0];
		tempArray[1] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[1];
		tempArray[2] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[2];
		tempArray[3] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[3];
		
		if ( Enemies_isArrayValid(tempArray,4,index) == true ){
			break;
		}
	}
	
	Enemies[index] -> Enemy_Front = randomFront;
	
	Enemies[index] ->Enemy_Position_Array[0] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[0];
	Enemies[index] ->Enemy_Position_Array[1] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[1];
	Enemies[index] ->Enemy_Position_Array[2] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[2];
	Enemies[index] ->Enemy_Position_Array[3] = randomFront + Enemies[index]->Enemy_Relative_Position_Array[3];
	
	Enemies[index]->Next_Enemy_Position_Array[0] = Enemies[index]->Enemy_Position_Array[0] + COLS;
	Enemies[index]->Next_Enemy_Position_Array[1] = Enemies[index]->Enemy_Position_Array[1] + COLS;
	Enemies[index]->Next_Enemy_Position_Array[2] = Enemies[index]->Enemy_Position_Array[2] + COLS;
	Enemies[index]->Next_Enemy_Position_Array[3] = Enemies[index]->Enemy_Position_Array[3] + COLS;
	
	Enemies[index]->Lives = 2;
	Enemies[index]->sizeof_enemyBullets = 10;
	Enemies[index]->rateMovement = 200;
	Enemies[index]->typeOfEnemy = 1;
	Enemies[index]->EnemyColor = Red;
	
	
	
}





void Enemies_move(){//moves type 1 enemies
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( Enemies[i] !=0 && Enemies[i]->typeOfEnemy == 1){
			LEDArray_TurnOffArray(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays);
			ArrayManip_copy(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays,
							Enemies[i]->Next_Enemy_Position_Array);
			Enemies[i]->Enemy_Front = Enemies[i]->Enemy_Position_Array[0];
		}
	}
}

bool Enemies_isArrayValid(int* P, int size, int index){
	if( Enemies_isArrayValidBounds(P,size)==true && Enemies_doesArrayCollideWithEnemies(P,size,index)==false){
		return true;
	}
	
	return false;
}

 bool Enemies_isArrayValidBounds( int* P, int size){
	int hitsLeft = 0;
	int hitsRight = 0;
	
	for ( int i=0; i<size; i++){
		if ( (P[i]-1) % COLS == 0){hitsLeft = 1;}
	}
	
	for ( int j=0; j<size; j++){
		if ( P[j] % COLS == 0){hitsRight = 1;}
	}
	
	if( (hitsRight && hitsLeft) ){
		return false;
	}else{
		return true;
	}
}
bool Enemies_doesArrayCollideWithEnemies(int* P, int size,int index){
	for (int i=0; i<sizeof_Enemies_Array; i++){
		if ( i != index && Enemies[i] !=0 && Enemies_doesArrayCollideWithEnemy(P,size,Enemies[i]) == true){
			return true;
		}
	}
	
	return false;
}



bool Enemies_doesArrayCollideWithEnemy( int* P, int size, Enemy* En){
	if (ArrayManip_doShareNum(P,size,En->Enemy_Position_Array,En->Size_Of_Arrays) == true || 
		ArrayManip_doShareNum(P,size,En->Next_Enemy_Position_Array,En->Size_Of_Arrays) == true){
		return true;
	}
	
	return false;
}



int* Enemies_getRandomNewPath(Enemy* En){
	int tempFront = Enemies_getRandomNewFront(En);
	
	int* tempPath = (int*)malloc(En->Size_Of_Arrays*sizeof(int));
	int tempsize = sizeof(tempPath)/sizeof(*tempPath);
	
	for ( int i=0; i < tempsize; i++){
		tempPath[i] = En->Enemy_Relative_Position_Array[i] + tempFront;
	}
	
	return tempPath;
}



void Enemies_clearOutOfBoundsEnemies(){
	for ( int i=0; i<sizeof_Enemies_Array; i++){
		if ( ArrayManip_allElementsGreaterThan(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays, COLS*ROWS)==true){
			LEDArray_TurnOffArray(Enemies[i]->Enemy_Position_Array,Enemies[i]->Size_Of_Arrays);
			free(Enemies[i]);
			Enemies[i] = 0;
		}
	}
}


bool Enemies_doEnemiesCollide( Enemy* En1, Enemy* En2){
	return ArrayManip_doShareNum(En1->Enemy_Position_Array, En1->Size_Of_Arrays,
									En2->Enemy_Position_Array,En2->Size_Of_Arrays);
}



void Enemies_loseLife(Enemy* En,int dmg){
	En->Lives = En->Lives- dmg;
}





int Enemies_getRandomNewFront(Enemy* En){
	int randNum = rand()%5;//*rand()%5;

	if(randNum == 0){return En->Enemy_Front -1;}//Left
	if(randNum == 1){return En->Enemy_Front +1;}//Right
	if(randNum == 2){return En->Enemy_Front +COLS;}//Down
	if(randNum == 3){return En->Enemy_Front +COLS + 1;}//Down and Right
	if(randNum == 4){return En->Enemy_Front +COLS - 1;}//Down and Left

	return 0;//shouldnt happen

}
#endif