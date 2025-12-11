
#include <iostream>
#include <conio.h>
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

void Draw() {
	
	system("cls");
	cout << "*********WELCOME TO SNAKE GAME********* \n";
	for (int i = 0; i < width+2; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ( j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "f";
			else
				cout<<" ";
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
	if (x > width || x < 0||y>height||y<0)
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
	Setup();
	while (!Gameover) {
		
		Draw();
		Input();
		Logic();
	}
	return 0;
}