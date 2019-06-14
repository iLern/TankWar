#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "symbol.h"
#include "tank.h"
#include "bullet.h"
#include "operation.h"

extern int map[MAXN][MAXN];
extern Bullet* bullets[MAX_BULLET];

Bullet* newBullet(Tank* father) {
	Bullet *ret = (Bullet*)malloc(sizeof(Bullet));

	if (!ret) return NULL;

	ret->isNew = True;
	ret->belongTo = father;
	ret->direction = father->direction;

	switch (father->direction) {
		case NORTH: 
			ret->x = father->x - 2;
			ret->y = father->y;
			break;
		case SOUTH:
			ret->x = father->x + 2;
			ret->y = father->y;
			break;
		case WEST:
			ret->x = father->x;
			ret->y = father->y - 2;
			break;
		case EAST:
			ret->x = father->x;
			ret->y = father->y + 2;
			break;
	}

	Bool flag = False;
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i] == NULL) {
			flag = True;
			bullets[i] = ret;
			break;
		}
	}

	return flag ? ret : NULL;
}

void printBullet(Bullet *bullet) {
	goToxy(bullet->y * 2, bullet->x);
	printf("o");
}

void clearBullet(Bullet *bullet) {
	goToxy(bullet->y * 2, bullet->x);
	printf(" ");
}

Bool isOutSide(Bullet *bullet) {
	if (bullet->x <= 0 || bullet->y <= 0 || bullet->x >= 40 || bullet->y >= 40) return True;
	return False;
}

Bool isHit(Bullet *bullet) {
	if (map[bullet->x][bullet->y] != 0) return True;
	return False;
}
