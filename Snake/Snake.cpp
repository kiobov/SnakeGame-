
#include <iostream>
#include <conio.h>
using namespace std;
const int width = 20;
const int  height = 20;
int x, y,  fruitX, fruitY, score ;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
bool Gameover ;


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