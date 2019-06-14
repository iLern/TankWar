#pragma once

#ifndef OPERATION_H_
#define OPERATION_H_

#include "symbol.h"
#include "tank.h"
#include "bullet.h"

void goToxy(int x, int y);
void clearMainScreen();
void hideCursor();
Bool chooseArrow();
void pause();

void init(int level, Tank *myTank);

void loadMap(int level);

Bool isMove(char c);
void bulletFly(Bullet* bullet[]);

Bool isOver(Tank *myTank);
void gameOver();
#endif