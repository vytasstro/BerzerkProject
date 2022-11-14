#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>
#include "Body.h";
#include "Player.h"

#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 15

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int score = 0;

bool enemyFlag[4];
int enemyX[4];
int enemyY[4];
char enemyDirection[4];

bool bulletFlag[20];
int bulletX[20];
int bulletY[20];
char bulletDirection[20];
int bulletIndex = 0;


void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder() {

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		gotoxy(i, SCREEN_HEIGHT); cout << "±";
	}

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		gotoxy(i, 0); cout << "±";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(0, i); cout << "±";
		gotoxy(SCREEN_WIDTH, i); cout << "±";
	}
}

void genBullet(char ch, int x, int y) {
	bulletFlag[bulletIndex] = true;
	if (ch == 'a' || ch == 'A') {
		//left
		bulletX[bulletIndex] = x - 1;
		bulletY[bulletIndex] = y;
		bulletDirection[bulletIndex] = 'a';
	}
	if (ch == 'd' || ch == 'D') {
		//right
		bulletX[bulletIndex] = x + 1;
		bulletY[bulletIndex] = y;
		bulletDirection[bulletIndex] = 'd';
	}
	if (ch == 's' || ch == 'S') {
		//down
		bulletX[bulletIndex] = x;
		bulletY[bulletIndex] = y + 1;
		bulletDirection[bulletIndex] = 's';
	}
	if (ch == 'w' || ch == 'w') {
		//up
		bulletX[bulletIndex] = x;
		bulletY[bulletIndex] = y - 1;
		bulletDirection[bulletIndex] = 'w';
	}
	bulletIndex ++;
	if (bulletIndex == 20)
		bulletIndex = 0;
}
int collision(int x, int y) {
	if (y < 1 || y >= 15 || x < 1 || x >= 30)
		return 1;
	for (int i = 0; i < 20; i++) {
		if (bulletFlag[i]) {
			if (bulletX[i] == x && bulletY[i] == y) {
				return 1;
			}
		}
	}

	return 0;
}
void drawBullets() {
	for (int i = 0; i < 20; i++) {
		if (bulletFlag[i]) {
			gotoxy(bulletX[i], bulletY[i]);
			cout << ".";
		}
	}
}
void eraseBullet(int ind) {
	gotoxy(bulletX[ind], bulletY[ind]); 
	cout << " ";
}
void moveBullet() {
	for (int i = 0; i < 20; i++) {
		if (bulletFlag[i]) {
			if (bulletDirection[i] == 'w') {
				if (collision(bulletX[i], bulletY[i] - 1) == 1) {
					eraseBullet(i);
					bulletFlag[i] = false;
					break;
				}
				bulletY[i]--;
			}
			else if (bulletDirection[i] == 's') {
				if (collision(bulletX[i], bulletY[i] + 1) == 1) {
					eraseBullet(i);
					bulletFlag[i] = false;
					break;
				}
				bulletY[i]++;
			}
			else if (bulletDirection[i] == 'd') {
				if (collision(bulletX[i]+1, bulletY[i]) == 1) {
					eraseBullet(i);
					bulletFlag[i] = false;
					break;
				}
				bulletX[i]++;
			}
			else
			{
				if (collision(bulletX[i] - 1, bulletY[i]) == 1) {
					eraseBullet(i);
					bulletFlag[i] = false;
					break;
				}
				bulletX[i]--;
			}
		}
	}
}
void eraseBullets() {
	for (int i = 0; i < 20; i++) {
		if (bulletFlag[i]) {
			gotoxy(bulletX[i], bulletY[i]);
			cout << " ";
		}
	}
}
void genEnemy(int ind) {
	if (enemyFlag[ind] == false) {
		enemyX[ind] = rand() % 29 + 1;
		enemyY[ind] = rand() % 14 + 1;
		enemyFlag[ind] = true;
	}
}
void drawEnemy(int ind) {
	if (enemyFlag[ind] == true) {
		gotoxy(enemyX[ind], enemyY[ind]);   
		cout << "@";
	}
}
void eraseEnemy(int ind) {
	if (enemyFlag[ind] == true) {
		gotoxy(enemyX[ind], enemyY[ind]); 
		cout << " ";
	}
}
void moveEnemy() {
	for (int i = 0; i < 3; i++) {
		if (enemyFlag[i]) {
			if (enemyDirection[i] == 'w') {
				if (collision(enemyX[i], enemyY[i] - 1) == 1) {
					eraseEnemy(i);
					enemyFlag[i] = false;
					break;
				}
				enemyY[i]--;
			}
			else if (enemyDirection[i] == 's') {
				if (collision(enemyX[i], enemyY[i] + 1) == 1) {
					eraseEnemy(i);
					enemyFlag[i] = false;
					break;
				}
				enemyY[i]++;
			}
			else if (enemyDirection[i] == 'd') {
				if (collision(enemyX[i]+1, enemyY[i]) == 1) {
					eraseEnemy(i);
					enemyFlag[i] = false;
					break;
				}
				enemyX[i]++;
			}
			else
			{
				if (collision(enemyX[i] - 1, enemyY[i]) == 1) {
					eraseBullet(i);
					bulletFlag[i] = false;
					break;
				}
				enemyX[i]--;
			}
		}
	}
}
void resetEnemy(int ind) {
	eraseEnemy(ind);
	enemyY[ind] = 4;
	genEnemy(ind);
}
int bulletHit() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			if (bulletFlag[i] && enemyFlag[j]) {
				if (bulletX[i] == enemyX[j] && bulletY[i] == enemyY[j])
				{
					eraseEnemy(j);
					enemyFlag[j] = false;
					eraseBullet(i);
					bulletFlag[i] = false;
					return 1;
				}
			}
		}
	}
	return 0;
}

void updateScore() {
	gotoxy(40 + 7, 5); cout << "Score: " << score << endl;
}
void gameover() {
	system("cls");
	cout << endl;
	cout << "\t\t--------------------------" << endl;
	cout << "\t\t-------- Game Over -------" << endl;
	cout << "\t\t-------- Score: "<<score<<"  -------" << endl << endl;
	cout << "\t\tPress any key to go back to menu.";
	_getch();
}

void play() {

	system("cls");
	gotoxy(5, 5); 
	cout << "Press any key to start";
	_getch();
	gotoxy(5, 5); 
	cout << "                      ";

	system("cls");
	drawBorder();
	Player player;

	while (1) {
		if (_kbhit()) {
			char ch = _getch();
			player.moveBody(ch);
			if (ch == 32) {
				genBullet(player.getDirection(), player.getx(), player.gety());
			}
			if (ch == 27) {
				break;
			}
		}
		genEnemy(0);
		genEnemy(1);
		genEnemy(2);

		gotoxy(player.getx(), player.gety());
		player.drawBody();

		for (int i = 0; i < 3; i++) {
			drawEnemy(i);
		}

	    drawBullets();

		if (collision(player.getx(), player.gety()) == 1) {
			gameover();
			return;
		}
		if (bulletHit() == 1) {
			score++;
			updateScore();
		}
		Sleep(200);

		gotoxy(player.getx(), player.gety());
		player.eraseBody();

		for (int i = 0; i < 3; i++) {
			eraseEnemy(i);
		}

		eraseBullets();
		moveBullet();
		int randNumb;
		for (int i = 0; i < 3; i++) {
			randNumb = rand() % 30;
			if (randNumb > 5)
				break;
			else if (randNumb == 5) {
				enemyDirection[i] = 'w';
				moveEnemy();
			}
			else if (randNumb == 4) {
				enemyDirection[i] = 's';
				moveEnemy();
			}
			else if (randNumb == 3) {
				enemyDirection[i] = 'a';
				moveEnemy();
			}
			else if (randNumb == 2) {
				enemyDirection[i] = 'd';
				moveEnemy();
			}
			else if (randNumb <= 1) {
				genBullet(enemyDirection[i], enemyX[i], enemyY[i]);
			}
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));

	do {
		system("cls");
		gotoxy(10, 5); cout << " ---------------------- ";
		gotoxy(10, 6); cout << " |       Berserk      | ";
		gotoxy(10, 7); cout << " ----------------------";
		gotoxy(10, 9); cout << "1. Start Game";
		gotoxy(10, 11); cout << "2. Quit";
		gotoxy(10, 13); cout << "Select option: ";
		char op = _getche();

		if (op == '1') play();
		else if (op == '2') exit(0);

	} while (1);

	return 0;
}