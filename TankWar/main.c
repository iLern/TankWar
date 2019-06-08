#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#include "frame.h"
#include "operation.h"
#include "symbol.h"
#include "tank.h"

int map[MAXN][MAXN];

int level = 1;
int score = 0;      

int main() {
	hideCursor();

	setFrame();
	showMenu();

	if (chooseArrow()) {
		Tank *myTank = newTank(20, 20, NORTH);
		init(myTank);
		while (True) {
			char ch = _getch();
			
			if (ch == 'x') openFire(myTank);
			else moveTank(myTank, ch);
		}
	}

	return 0;
}
