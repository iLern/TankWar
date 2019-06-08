#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "operation.h"
#include "symbol.h"
#include "tank.h"

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
		char button = _getch(); //_getch() is safe

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

extern int level, score;

void init(Tank *myTank) {
	clearMainScreen();
	printTank(myTank);

	goToxy(97, 2);
	printf("%d", level);
	goToxy(102, 5);
	printf("%d   ", score);
	goToxy(100, 13);
	printf("ÕýÔÚÓÎÏ·");
}
