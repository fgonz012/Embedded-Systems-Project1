#ifndef __ENEMY_BULLETS_H__
#define __ENEMY_BULLETS_H__

#include "colors.h"
#include "Enemies.h"


typedef struct EnemyBullet{
	
	int position;
	int dmg;
	color col;
	
	}EnemyBullet;


EnemyBullet* EnemyBulletsArray[20] = {0};










#endif