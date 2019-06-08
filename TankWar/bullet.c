#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "symbol.h"
#include "tank.h"
#include "bullet.h"
#include "operation.h"

extern int map[MAXN][MAXN];

Bullet* newBullet(Tank* father) {
	Bullet *ret = (Bullet*)malloc(sizeof(Bullet));

	ret->belongTo = father;
	ret->direction = father->direction;

	switch (father->direction) {
		case UP: 
			ret->x = father->x;
			ret->y = father->y - 2;
			break;
		case DOWN:
			ret->x = father->x;
			ret->y = father->y + 2;
			break;
		case LEFT:
			ret->x = father->x - 2;
			ret->y = father->y;
			break;
		case RIGHT:
			ret->x = father->x + 2;
			ret->y = father->y;
			break;
	}

	return ret;
}

void clearBullet(Bullet *bullet) {
	goToxy(bullet->x, bullet->y);
	printf(" ");
	free(bullet);
	bullet = NULL;
}

Bool isHit(Bullet *bullet) {
	if (bullet->x >= MAXN || bullet->x <= 0 || bullet->y >= MAXN || bullet->y <= 0) {
		clearBullet(bullet);
	}
}