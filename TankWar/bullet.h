#pragma once

#ifndef BULLET_H_
#define BULLET_H_

#include "tank.h"
#include "symbol.h"

typedef struct Bullet {
	int x, y;
	enum Direction direction;
	Tank *belongTo;
} Bullet;

Bullet* newBullet(Tank *father);
Bool isHit(Bullet *bullet);
void clearBullet(Bullet *bullet);
#endif