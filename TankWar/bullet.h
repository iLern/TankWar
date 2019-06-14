#pragma once

#ifndef BULLET_H_
#define BULLET_H_

#include "tank.h"
#include "symbol.h"

typedef struct Bullet {
	int x, y; //in array;
	enum Direction direction;

	Bool isNew;

	Tank *belongTo;
} Bullet;

Bullet* bullets[MAX_BULLET];

Bullet* newBullet(Tank *father);

void printBullet(Bullet *bullet);
void clearBullet(Bullet *bullet);

Bool isOutSide(Bullet *bullet);
Bool isHit(Bullet *bullet);
#endif