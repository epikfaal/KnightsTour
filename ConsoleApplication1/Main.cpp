#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Knight.h"


int main(){
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
