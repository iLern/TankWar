#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "symbol.h"
#include "tank.h"
#include "bullet.h"
#include "operation.h"

extern char map[MAXN][MAXN];

Tank* newTank(int x, int y, enum Direction dir) {
	Tank *ret = (Tank*)malloc(sizeof(Tank));
	ret->x = x;
	ret->y = y;
	ret->direction = dir;

	return ret;
}

void printTank(Tank *tank) {
	goToxy(tank->x, tank->y - 1);
	printf("%s", shapeOfTank[tank->direction][0]);
	goToxy(tank->x, tank->y);
	printf("%s", shapeOfTank[tank->direction][1]);
	goToxy(tank->x, tank->y + 1);
	printf("%s", shapeOfTank[tank->direction][2]);
}

void clearTank(Tank *tank) {
	goToxy(tank->x, tank->y - 1);
	printf("   ");
	goToxy(tank->x, tank->y);
	printf("   ");
	goToxy(tank->x, tank->y + 1);
	printf("   ");
}

void turnTank(Tank *tank, char dir) {
	enum Direction newDir;

	if (dir == UP) newDir = NORTH;
	else if (dir == DOWN) newDir = SOUTH;
	else if (dir == LEFT) newDir = WEST;
	else if (dir == RIGHT) newDir = EAST;
	else return;

	if (tank->direction != newDir) tank->direction = newDir;
}

void moveTank(Tank *tank, char dir) {
	clearTank(tank);
	turnTank(tank, dir);

	switch (dir) {
		case UP: tank->y--; break;
		case DOWN: tank->y++; break;
		case LEFT: tank->x--; break;
		case RIGHT: tank->x++; break;
	}

	printTank(tank);
}

void openFire(Tank *tank) {
	Bullet *bullet = newBullet(tank);

	goToxy(bullet->x, bullet->y);
	printf(".");
}