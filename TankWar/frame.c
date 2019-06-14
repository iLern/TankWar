#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#include "frame.h"
#include "operation.h"
#include "symbol.h"

void setFrame() {
	system("mode con cols=112 lines=42");

	printf("  ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  ");
	printf(" |═════════════════════════ |\n");
	for (int i = 0; i < 14; i++) {
		printf("▕                                                                              ▏");
		printf(" |                          |\n");
	}
	printf("▕                                                                              ▏");
	printf(" |═════════════════════════ |\n");
	for (int i = 0; i < 24; i++) {
		printf("▕                                                                              ▏");
		printf(" |                          |\n");
	}
	printf("  ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ");
	printf(" |═════════════════════════ |\n");

	sideScreen();
}

void sideScreen() {
	goToxy(93, 2);
	printf("第     关");
	goToxy(92, 5);
	printf("分  数：");
	goToxy(92, 7);
	printf("生  命：");
	goToxy(86, 9);
	printf("剩余敌方坦克：");
	goToxy(86, 13);
	printf("当前游戏状态：");
	goToxy(94, 19);
	goToxy(94, 24);
	printf("帮  助");
	goToxy(86, 27);
	printf("方向键  ←↑→↓  移动");
	goToxy(93, 29);
	printf("x 键 射击");
	goToxy(90, 37);
	printf("Esc键  暂停游戏");
}

void showMenu() {
	Bool isStart = True;

	goToxy(37, 10);
	printf("MENU");

	goToxy(BEGIN_POS_X, BEGIN_POS_Y);
	printf("*** START GAME ***");

	goToxy(END_POS_X, END_POS_Y);
	printf("*** QUIT  GAME ***");

	goToxy(25, 20);
	printf("--->");
}
