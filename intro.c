#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void gotoxy(int x, int y);

void CursorView();

void map();

int key() {
	return _getch();
}

int main(void) {
	srand((unsigned)time(NULL));
	CursorView();
	int i = 0, j = 0;

	int x1 = 30, y1 = 12;//머리의 좌표값
	int alt_x = 0, alt_y = 0;
	int px = rand() % 23 + 19, py = rand() % 23 + 2;
	int score = 0;
	int tracex[ 50 ] = { 10 , 10 , 10, 10, 0, };//마디마디의 X좌표값
	int tracey[ 50 ] = { 10 , 10 , 10, 10, 0, };//마디마디의 Y좌표값


	char kpt1[5] = "○";

	char peed[3] = "♣";
	
	map();

	gotoxy(27, 6);
	printf("< S N A K E >");
	gotoxy(24, 8);
	printf("[ PRESS ENTER TO START ]");

	gotoxy(28, 12);
	printf("LOADING");

	while (1) {
		if (_kbhit()) {
			if (key() == 13) {
				system("cls");
				map();
				break;
			}
		}
		gotoxy(28, 13);
		for (i = 0; i < 7; i++) {
			if (i != j % 7) printf("□");
			else			printf("■");
		}
		j++;
		Sleep(200);
	}

	gotoxy(3, 12);
	printf("조작법 : 방향키");
	
	gotoxy(50, 12);
	printf("점수 : %d", score);

	gotoxy(px, py);
	printf("%s", peed);

	gotoxy(x1, y1);

	
	while (1) {
		if (_kbhit()) {
			if (key() == 224 || key() == 0) {
				switch (key()) {
				case LEFT:
					if (alt_x != 1) {
						alt_x = -1;
						alt_y = 0;
						break;
					}
					else break;

				case RIGHT:
					if (alt_x != -1) {
						alt_x = 1;
						alt_y = 0;
						break;
					}
					else break;

				case UP:
					if (alt_y != 1) {
						alt_y = -1;
						alt_x = 0;
						break;
					}
					else break;

				case DOWN:
					if (alt_y != -1) {
						alt_y = 1;
						alt_x = 0;
						break;
					}
					else break;

				default:
					break;
				}
			}
			else continue;
		}

		if (x1 == px && y1 == py) {
			score++;
			gotoxy(50, 12);
			printf("점수 : %d", score);
			
			px = rand() % 23 + 19, py = rand() % 23 + 2;
			gotoxy(px, py);
			printf("%s", peed);
		}

		if (x1 == 18 || x1 == 42 || y1 == 1 || y1 == 25) {//외벽에 닿으면 죽는다.
			system("cls");
			gotoxy(28, 12);
			printf("점수 : %2d", score);
			return 0;
		}

		if (alt_x ==  1) x1++;
		if (alt_x == -1) x1--;
		if (alt_y ==  1) y1++;
		if (alt_y == -1) y1--;

		gotoxy(x1, y1);
		printf("%s", kpt1);
		Sleep(200);

		tracex[score + 3] = x1;
		tracey[score + 3] = y1;

		for (i = 1;i < score + 4; i++){

			tracex[i - 1] = tracex[i];
			tracey[i - 1] = tracey[i];

			if (i >= 1 && i < score + 2 && tracex[i] == x1 && tracey[i] == y1) { //꼬리에 닿으면 죽는다.
				system("cls");
				gotoxy(28, 12);
				printf("점수 : %2d", score);
				return 0;
			}
		}
		gotoxy(tracex[0], tracey[0]);
		printf("  ");
	}
	return 0;
}

void gotoxy(int x, int y) {
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void map() {
	for (int i = 1; i <= 25; i++) {
		for (int j = 1; j <= 25; j++) {
			if (i == 1 || i == 25 || j == 1 || j == 25) {
				gotoxy(j + 17, i);
				printf("■");
			}
			else printf(" ");
		}
		printf("\n");
	}
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}