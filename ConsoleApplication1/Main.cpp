#include <stdio.h>
#include <cstdlib>
#include "Knight.h"
#include <Windows.h>


int main(HINSTANCE module, HINSTANCE, PWSTR, int){
	Knight* knight = new Knight();
	knight->printBoard(8);
	knight->printBoard(7);
	knight->printBoard(6);
	knight->printBoard(5);
	knight->printBoard(4);
	knight->printBoard(3);
	knight->printBoard(2);
	knight->printBoard(1);
	system("pause");
}
