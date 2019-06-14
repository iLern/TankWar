#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include "frame.h"
#include "operation.h"
#include "symbol.h"
#include "tank.h"
#include "map.h"

int map[MAXN][MAXN];
extern Bullet* bullets[MAX_BULLET];
extern Tank* aiTanks[MAX_TANK];

int level = 1;
int score = 0;
int remain = 10;

int main() {
	hideCursor();

	setFrame();
	showMenu();

	if (chooseArrow()) {
		Tank *myTank = newTank(37, 14, NORTH);
		init(level, myTank);

		for (unsigned int i = 0; ; i++) {
			if (i % SPEED == 0) {
				int pos = rand() % 2;
				enum Direction dir = rand() % 4;
				addAiTank(pos, dir);

				bulletFly(bullets);

				if (i % (SPEED * 5) == 0) moveAiTank(aiTanks);
			}

			if (myTank->coolDownTime > 0) myTank->coolDownTime--;

			for (int i = 0; i < MAX_TANK; i++) {
				if (aiTanks[i] != NULL && remain > 0) {
					if (tankIsHit(aiTanks[i])) aiTanks[i]->life--;
					if (aiTanks[i]->life == 0) {
						clearTank(aiTanks[i]);
						free(aiTanks[i]);
						aiTanks[i] = NULL;

						remain--;
						goToxy(102, 9);
						printf("%d   ", remain);

						score++;
						goToxy(102, 5);
						printf("%d   ", score);
					}
				}
				if (aiTanks[i]) {
					openFire(aiTanks[i]);
				}
			}

			if (tankIsHit(myTank)) {
				myTank->life--;
				goToxy(102, 7);
				printf("%d   ", myTank->life);
			}

			if (isOver(myTank)) gameOver();
			if (remain == 0) win();

			char ch = '\0';
			if (kbhit()) ch = _getch();
			
			if (ch == 'x') openFire(myTank);
			else if (isMove(ch)) moveTank(myTank, ch);
			else if (ch == ESC) pause();
		}
	}

	return 0;
}
