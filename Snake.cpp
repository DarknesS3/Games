#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <windows.h>
#include <stack>
#include <time.h>
using namespace std;
// Prototypes
void clear(int a); // скорость игры,  а - параметр скорости
void clone_snake_to_field(int mas[20][40], int mas1[20][40], int h, int w);
void setcur(int x, int y);//установка курсора на позицию  x y (Убирает мерцание консоли)
void field_snake(int mas[20][40],  int h, int w );
void field_draw(int mas[20][40],  int h, int w, int  c);
void bug_food(int mas[20][40], int h, int w, int c);
char game_over();
// Global data
int snake_i = 10;// координаты головы змеи змеи
int snake_j = 10; 
int n_len = 5; //начальная длина змеи
int f=15; //начальные координаты еды
int g=15;
int score = 0;
int main()
{
	srand(time(NULL));
const 	int a = 20;
const 	int b = 40;
bool place=true;
int 	mass[a][b];
int snake_mass[a][b];
int as;
int bs;
int speed, speed_one=0;
stack<int> my_snake_i;	
stack<int> my_snake_j;
stack<int> rev_snake_i;
stack<int> rev_snake_j;
char move1,move_ex='w', move='d';
do {
	system("color b");
	cout << "\n\tHi! Please chose some parameters, before start GAME:";
	do {
		cout << "\n\tFor move the Snake use: w,a,s,d and q - for exit\n\tEnter a level of difficult(1-10):";
		cin >> speed_one;
	} while (speed_one < 1 || speed_one >10);
	switch (speed_one)
	{
	case 1:speed = 220; break;
	case 2:speed = 205; break;
	case 3:speed = 190; break;
	case 4:speed = 170; break;
	case 5:speed = 145; break;
	case 6:speed = 115; break;
	case 7:speed = 100; break;
	case 8:speed = 75; break;
	case 9:speed = 50; break;
	case 10:speed = 15; break;
	}
	system("CLS");
	system("color 1a");
	for (int i = 10; i > n_len; --i) { my_snake_j.push(i); my_snake_i.push(10); } // начальная позиция змеи.
	while (move != 'q')
	{
		if (_kbhit()) {
			move1 = (char)_getch();
			if (move1 == 'w' || move1 == 'a' || move1 == 's' || move1 == 'd' || move1 == 'q')
				if ((move1 == 'a' && move != 'd') || (move1 == 'w' && move != 's') || (move1 == 's' && move != 'w') || (move1 == 'd' && move != 'a') || move1 == 'q')
					move = move1;
		}

		switch (move)
		{
		case 'a':
			snake_j--;
			break;
		case 'w':
			snake_i--;
			break;
		case 's':
			snake_i++;
			break;
		case 'd':
			snake_j++;
			break;
		}
		if (snake_mass[snake_i][snake_j] == 174) break;//если змея себя укусила - выход	
		if (snake_i == 0) { snake_i = a - 2; }
		else if (snake_i == a - 1) { snake_i = 1; }
		else as = snake_i; my_snake_i.push(as);//проверка на выход за пределы массива
		if (snake_j == 0) { snake_j = b - 2; }
		else if (snake_j == b - 1) { snake_j = 1; }
		else bs = snake_j; my_snake_j.push(bs);//проверка на выход за пределы массива

		field_snake(mass, a, b); // обнуляем основное поле
		field_snake(snake_mass, a, b); // обнуляем поле для змеи
		if (place)snake_mass[f][g] = 35;
		for (int i = 0; i < n_len; ++i) // выводим координаты змеи
		{
			if (snake_mass[my_snake_i.top()][my_snake_j.top()] == 35) 
				bug_food(snake_mass, a, b, speed); 
			if (i == 0)snake_mass[my_snake_i.top()][my_snake_j.top()] = 31;  //символ для головы змеи
			else snake_mass[my_snake_i.top()][my_snake_j.top()] = 174;
			rev_snake_i.push(my_snake_i.top());
			rev_snake_j.push(my_snake_j.top());
			my_snake_i.pop();
			my_snake_j.pop();
		}
		for (int i = 0; i < n_len; i++)
		{
			my_snake_i.push(rev_snake_i.top());
			my_snake_j.push(rev_snake_j.top());
			rev_snake_i.pop();
			rev_snake_j.pop();
		}
		clone_snake_to_field(mass, snake_mass, a, b); // налаживаем поле для змеи на основное поле

		field_draw(mass, a, b, speed_one);
		clear(speed); // обновляем поле		
	}
	move_ex=game_over();
} while (move_ex != 'q');
	return 0;
}
void clear(int a)
{
	Sleep(a);
	setcur(0, 0);
}
void field_snake(int mas[20][40],  int h, int w)
{
	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
		{
			if( (i && j) == 0 || (i==h-1) || (j == w -1) ) mas[i][j]=219;
			else mas[i][j] = 32; 
		}
		mas[snake_i][snake_j] = 219;
}
void field_draw(int mas[20][40],  int h, int w, int c)
{
	cout << "\n\t\t\tSNAKE v1.0\n\n";
	for(int i = 0; i < h; i++)
	{
		cout << "\t\t\t";
			for(int j = 0; j < w; j++)
			cout << (char)mas[i][j];
		cout << endl;
		}
	cout << "\n\t\t\t # Level: " << c << "\n\t\t\t # Score: " << score << "\n\t\t\t # Lenght: " << n_len;
}
void clone_snake_to_field(int mas[20][40], int mas1[20][40], int h, int w)
{
	for(int i = 0; i < h; i++)
		for(int j = 0; j< w; j++)
			mas[i][j]=mas1[i][j];
}
void bug_food(int mas[20][40], int h, int w, int c )
{
	do{
     f = rand()%(h-2)+1;
	 g = rand()%(w-2)+1;
	}while(mas[f][g]!=32);
	n_len++;
	score +=50 ;
}
void setcur(int x, int y)//установка курсора на позицию  x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
char game_over()
{
	char c1;
	system("color 1c");
		cout << "Game Over! RePlay?(y/n): "; cin >> c1;
	if (c1 == 'y')c1 = 'w';
	else if (c1 == 'n')c1 = 'q';
	system("CLS");
		return c1;
}