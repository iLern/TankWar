#pragma once

#ifndef OPERATION_H_
#define OPERATION_H_

#include "symbol.h"
#include "tank.h"

void goToxy(int x, int y);
void clearMainScreen();
void hideCursor();
Bool chooseArrow();

void init(Tank *myTank);
#endif