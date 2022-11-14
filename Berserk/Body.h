#pragma once
#include <string>
#include <windows.h>
#include <consoleapi2.h>
#include <processenv.h>
#include <WinBase.h>
#include <iostream>
using namespace std;

class Body
{
private:
	int x, y;
	boolean flag;
	char direction;

public:
	Body() {
		x = rand() % 29 + 1;
		y = rand() % 14 + 1;
		flag = true;
		direction = 'w';
	};

	void setx(int newx) {
		x = newx;
	}
	int getx() {
		return x;
	}
	void sety(int newy) {
		x = newy;
	}
	int gety() {
		return y;
	}
	void setDirection(char newDirection) {
		direction = newDirection;
	}
	char getDirection() {
		return direction;
	}

	void drawBody() {
		cout << '@';
	}
	void eraseBody() {
		cout << " ";
	}

	int checkCollision() {
		if (x > 29 && x < 1)
			return 1;
		if (y > 14 && y < 1)
			return 1;
		if (x == 8 && y >= 4 && y <= 10)
			return 1;
		if (x == 18 && y >= 4 && y <= 10)
			return 1;
		return 0;
	}

	void moveBody(char curDirection) {
		if (curDirection == 'a' || curDirection == 'A') {
			//left
			x--;
			direction = curDirection;
			//checkCollision(x, y, type);
		}
		if (curDirection == 'd' || curDirection == 'D') {
			//right
			x++;
			direction = curDirection;
		}
		if (curDirection == 's' || curDirection == 'S') {
			//down
			y++;
			direction = curDirection;
		}
		if (curDirection == 'w' || curDirection == 'w') {
			//up
			//eraseBody();
			y--;
			direction = curDirection;
			//if (checkCollision() == 1)
			//	drawBody();
			//checkCollision(x, y, type);
		}
	}
};
