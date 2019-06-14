#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include "operation.h"
#include "symbol.h"
#include "tank.h"
#include "bullet.h"

void goToxy(int x, int y) {
	COORD  coord;
	coord.X = x;
	coord.Y = y;
	HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a, coord);
}

void clearMainScreen() {
	for (int i = 1; i < 40; i++) {
		goToxy(2, i);
		printf("                                                                              ");
	}
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

Bool chooseArrow() {
	Bool flag = True;

	do {
		char button = getch(); //_getch() is safe

		if (button == UP && !flag) {
			goToxy(25, 23);
			printf("    ");
			goToxy(25, 20);
			printf("--->");

			flag = True;
		} else if (button == DOWN && flag) {
			goToxy(25, 20);
			printf("    ");
			goToxy(25, 23);
			printf("--->");

			flag = False;
		}

		if (button == ENTER) break;
		if (button == ESC) {
			flag = False;
			break;
		}

	} while (True);

	return flag;
}

extern int level, score, remain;
extern Bullet* bullets[MAX_BULLET];
extern Tank* aiTanks[MAX_TANK];

void init(int level, Tank *myTank) {
	srand(time(NULL));

	clearMainScreen();
	loadMap(level);
	printTank(myTank);

	for (int i = 0; i < MAX_BULLET; i++) {
		bullets[i] = NULL;
	}

	for (int i = 0; i < MAX_TANK; i++) {
		aiTanks[i] = NULL;
	}

	goToxy(97, 2);
	printf("%d", level);
	goToxy(102, 5);
	printf("%d   ", score);
	goToxy(102, 7);
	printf("%d   ", myTank->life);
	goToxy(102, 9);
	printf("%d   ", remain);
	goToxy(100, 13);
	printf("正在游戏");
}

void pause() {
	goToxy(100, 13);
	printf("游戏暂停\n");
	goToxy(88, 17);
	printf("按 回车 键回到游戏\n");
	goToxy(88, 18);
	printf("按 ESC  键退出游戏\n");
	while (True) {
		char op = '\0';
		if (kbhit()) op = _getch();
		if (op == ENTER) {
			goToxy(100, 13);
			printf("正在进行\n");
			goToxy(88, 17);
			printf("                   ");
			goToxy(88, 18);
			printf("                   ");
			break;
		} else if (op == ESC) exit(0);
	}
}

Bool isMove(char c) {
	if (c == UP || c == DOWN || c == LEFT || c == RIGHT) return True;

	return False;
}

extern int map[MAXN][MAXN];
void bulletFly(Bullet* bullet[]) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullet[i] != NULL) {
			if (bullet[i]->isNew) {
				bullet[i]->isNew = False;
				printBullet(bullet[i]);
			} else {
				clearBullet(bullet[i]);
				switch (bullet[i]->direction) {
					case NORTH: bullet[i]->x--; break;
					case SOUTH: bullet[i]->x++; break;
					case EAST: bullet[i]->y++; break;
					case WEST: bullet[i]->y--; break;
				}

				if (!isOutSide(bullet[i])) {
					printBullet(bullet[i]);
					if (isHit(bullet[i])) {
						map[bullet[i]->x][bullet[i]->y] = 0;
						clearBullet(bullet[i]);
						free(bullet[i]);
						bullet[i] = NULL;
					}
				} else {
					clearBullet(bullet[i]);
					free(bullet[i]);
					bullet[i] = NULL;
				}
			}
		}
	}
}

extern int graph[6][41][41];
extern int map[MAXN][MAXN];
void loadMap(int level) {
	for (int i = 0; i < 41; i++) {
		for (int j = 0; j < 41; j++) {
			map[i][j] = graph[level - 1][i][j];

			if (map[i][j] == 6) {
				goToxy(j * 2, i);
				printf("■");
			} else if (map[i][j] == 2 || map[i][j] == 1) {
				goToxy(j * 2, i);
				printf("▓");
			}
		}
	}

	goToxy(38, 37);
	printf("◣★◢");
	goToxy(38, 38);
	printf("  ▅ ");
	goToxy(38, 39);
	printf("◢▅◣");
}

extern int remain;
Bool isOver(Tank *myTank) {
	if (myTank->life == 0) return True;

	int x = 37; int y = 19;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (map[x + i][y + i] != 9) return True;
		}
	}

	return False;
}

void gameOver() {
	clearMainScreen();

	goToxy(35, 10);
	printf("Game Over\n");

	goToxy(33, 12);
	printf("你的得分 : %d", score);

	goToxy(31, 20);
	printf("按 ESC 键退出游戏");

	pause();
}

void win() {
	clearMainScreen();

	goToxy(35, 10);
	printf("You Win !!\n");

	goToxy(33, 12);
	printf("你的得分 : %d", score);

	goToxy(31, 20);
	printf("按 ESC 键退出游戏");

	pause();
}
