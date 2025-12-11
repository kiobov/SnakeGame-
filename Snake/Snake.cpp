
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
const int width = 20;
const int  height = 20;
int x, y,  fruitX, fruitY, score ;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
bool Gameover ;
int tailX[100], tailY[100];
int nTail;



void Setup() {
	
	Gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand()% width;
	fruitY = rand() % height;

}

void Menu() {
	system("cls");
	cout << "===================== \n";
	cout << "WELCOME TO SNAKE GAME \n";
	cout << "===================== \n\n\n";

	cout << "Enter \"S\" to start game.\n";
	cout << "Enter \"Q\" to quit game.\n";
	cout << "Enter \"P\" to pause.\n";

	cout << "Enter key Option\n";

}
void Pausegame() {

	cout << "Game Paused\n";
	cout << "Enter \"R or r\" Resume.....\n ";
	while (true) {

		if (_kbhit()) {
			char key = _getch();
			if ("r" || "R") {
				break;
			}
		}
	}

}

void SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearScreen()
{
	COORD topLeft = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), topLeft);
}

void Draw() {
	
	system("cls");
	
	
	for (int i = 0; i < width+2; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ( j == 0)
				cout << "#";
			if (i == y && j == x) {
				SetColor(10); cout << "O"; SetColor(7);
			}
			else if (i == fruitY && j == fruitX) {
				SetColor(12); cout << "f"; SetColor(7);
			}
			else {
				//add the body size when we eat 
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i)
					{
						SetColor(10);
						cout << "o";
						SetColor(7);
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if ( j ==width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++) 
		cout << "#";
	cout << endl;
	
	cout << "Score: "<<score;

}
void Input() {

	//get character from keyboard 
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
		dir=LEFT; break;
		case 'd':
		dir=RIGHT; break;

		case'w':
		dir=UP; break;
		case 's':
		dir=DOWN; break;

		case 'P':
		case 'p':
			Pausegame(); break;

		case 'x':
			Gameover = true; break;
		}
	}

}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		 prev2X = tailX[i];
		 prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
	case LEFT: x--;  break;
	case RIGHT: x++;  break;
	case UP: y--;  break;
	case DOWN: y++;  break;
	default: break;
	}
	//game over when you hit the walls
	//if (x > width || x < 0||y>height||y<0)
	//	Gameover = true;
	//hit wall come from other end 
	if (x > width) x = 0; else if (x < 0)x = width - 1;
	if (y > height) y = 0; else if (y < 0)y = height - 1;
	//terminate when it eat  body
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			Gameover = true;


	//increase score 
	if (x == fruitX && y == fruitY) {
		score  += 10;
		//randomly put fruit in map
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}


int main() {
	Menu();
	char Choice;

	cin >> Choice;
	if (Choice == 'Q'||Choice == 'q')
		return 0;
	
	if (Choice == 'S'||Choice =='s') {
		Setup();
		Menu();
		while (!Gameover) {

			Draw();
			Input();
			Logic();
		}
		return 0;
	}
}