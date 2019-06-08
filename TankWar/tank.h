#pragma once

#ifndef TANK_H_
#define TANK_H_

#include "symbol.h"
static char shapeOfTank[4][4][4] =
{
	{
		" o ",
		"ooo",
		"ooo"
	},
	{
		"ooo",
		"ooo",
		" o "
	},
	{
		"oo ",
		"ooo",
		"oo"
	},
	{
		" oo",
		"ooo",
		" oo"
	}
};

typedef struct Tank {
	int x, y;
	enum Direction direction;
} Tank;

Tank* newTank(int x, int y, enum Direction dir);
void printTank(Tank *tank);
void clearTank(Tank *tank);
void turnTank(Tank *tank, char dir);
void moveTank(Tank *tank, char dir);
void openFire(Tank *tank);

#endif
