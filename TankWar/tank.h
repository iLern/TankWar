#pragma once

#ifndef TANK_H_
#define TANK_H_

#include "symbol.h"

static char shapeOfTank[4][7][7] =
{
	{
		" O ",
		"OOO",
		"OOO"
	},
	{
		"OOO",
		"OOO",
		" O "
	},
	{
		"OO",
		"OOO",
		"OO"		
	},
	{
		" OO",
		"OOO",
		" OO"
	}
};

typedef struct Tank {
	int x, y; //in array
	enum Direction direction;
	int life;

	int coolDownTime;
} Tank;

Tank* aiTanks[MAX_TANK];

Tank* newTank(int x, int y, enum Direction dir);
void printTank(Tank *tank);
void clearTank(Tank *tank);
void turnTank(Tank *tank, char dir);
Bool canMove(Tank *myTank, char dir);
void moveTank(Tank *tank, char dir);
void openFire(Tank *tank);
Bool tankIsHit(Tank *tank);

// about AI
void addAiTank(int pos, enum Direction dir);
void moveAiTank(Tank* aiTanks[MAX_TANK]);
#endif
