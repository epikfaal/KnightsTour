#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Knight.h"


int main(){
	Knight* knight = new Knight();
	std::string startingposition;

	std::cout << "Please enter the knights starting position (type \"random\" for random)" << std::endl;
	std::cin >> startingposition;
	if(!knight->startPath(startingposition.c_str())) exit(0);

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
