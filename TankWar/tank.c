#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "symbol.h"
#include "tank.h"
#include "bullet.h"
#include "operation.h"

extern int map[MAXN][MAXN];

// x, y in array
Tank* newTank(int x, int y, enum Direction dir) {
	Tank *ret = (Tank*)malloc(sizeof(Tank));

	ret->x = x;
	ret->y = y;
	ret->direction = dir;
	ret->coolDownTime = 0;
	ret->life = 3;

	return ret;
}

void printTank(Tank *tank) {
	goToxy((tank->y * 2) - 1, tank->x - 1);
	printf("%s", shapeOfTank[tank->direction][0]);
	goToxy((tank->y * 2) - 1, tank->x);
	printf("%s", shapeOfTank[tank->direction][1]);
	goToxy((tank->y * 2) - 1, tank->x + 1);
	printf("%s", shapeOfTank[tank->direction][2]);
}

void clearTank(Tank *tank) {
	goToxy((tank->y * 2) - 1, tank->x - 1);
	printf("     ");
	goToxy((tank->y * 2) - 1, tank->x);
	printf("     ");
	goToxy((tank->y * 2) - 1, tank->x + 1);
	printf("     ");
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

//up down right left
Bool canMove(Tank *tank, char dir) {
	Bool flag = False;
	int newX = -1; int newY = -1;
	switch (dir) {
		case UP:
			newX = tank->x - 2;
			if (map[newX][tank->y] == 0 && map[newX][tank->y - 1] == 0 && map[newX][tank->y + 1] == 0) flag = True;
			
			break;
		case DOWN:
			newX = tank->x + 2;
			if (map[newX][tank->y] == 0 && map[newX][tank->y - 1] == 0 && map[newX][tank->y + 1] == 0) flag = True;
			
			break;
		case RIGHT:
			newY = tank->y + 2;
			if (map[tank->x][newY] == 0 && map[tank->x - 1][newY] == 0 && map[tank->x + 1][newY] == 0) flag = True;
			
			break;
		case LEFT:
			newY = tank->y - 2;
			if (map[tank->x][newY] == 0 && map[tank->x - 1][newY] == 0 && map[tank->x + 1][newY] == 0) flag = True;
			break;
	}
	return flag;
}

void moveTank(Tank *tank, char dir) {
	clearTank(tank);
	turnTank(tank, dir);

	if (canMove(tank, dir)) {
		switch (dir) {
			case UP: tank->x--; break;
			case DOWN: tank->x++; break;
			case LEFT: tank->y--; break;
			case RIGHT: tank->y++; break;
		}
	}

	printTank(tank);
}

void openFire(Tank *tank) {
	Bullet *bullet = NULL;
	if (tank->coolDownTime == 0) 
		bullet = newBullet(tank);
	
	tank->coolDownTime = 500;
}

extern Bullet* bullets[MAX_BULLET];
Bool tankIsHit(Tank *tank) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullets[i] != NULL) {
			if (bullets[i]->x >= tank->x - 1 && bullets[i]->x <= tank->x + 1 
				&& bullets[i]->y >= tank->y - 1 && bullets[i]->y <= tank->y + 1) {
				clearBullet(bullets[i]);
				free(bullets[i]);
				bullets[i] = NULL;
				return True;
			}
		}
	}

	return False;
}


//about AI
extern Tank* aiTanks[MAX_TANK];
void addAiTank(int pos, enum Direction dir) {
	for (int i = 0; i < MAX_TANK; i++) {
		if (aiTanks[i] == NULL) {
			if (pos == 0) aiTanks[i] = newTank(2, 8, dir);
			else if (pos == 1) aiTanks[i] = newTank(2, 20, dir);
			else if (pos == 2) aiTanks[i] = newTank(2, 32, dir);

			printTank(aiTanks[i]);

			break;
		}
	}
}

void moveAiTank(Tank* aiTanks[MAX_TANK]) {
	for (int i = 0; i < MAX_TANK; i++) {
		if (aiTanks[i] != NULL) {
			int dir = 0;
			switch (aiTanks[i]->direction) {
				case NORTH: dir = UP;
				case SOUTH: dir = DOWN;
				case EAST: dir = RIGHT;
				case WEST: dir = LEFT;
			}

			int newDir = dir;
			if (canMove(aiTanks[i], dir)) moveTank(aiTanks[i], dir);
			else {
				while (newDir == dir) {
					int x = rand() % 4;
					switch (x) {
						case 0: newDir = UP; break;
						case 1: newDir = DOWN; break;
						case 2: newDir = LEFT; break;
						case 3: newDir = RIGHT; break;
						default: break;
					}
				}

				moveTank(aiTanks[i], newDir);
				moveTank(aiTanks[i], newDir);
				moveTank(aiTanks[i], newDir);
			}
		}
	}
}
