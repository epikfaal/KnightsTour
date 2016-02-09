#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Knight.h"


int main(){
	Knight* knight = new Knight();
	std::string startingposition;
	knight->initBoard(8, 8);
	std::cout << "Please enter the knights starting position (type \"random\" for random)" << std::endl;
	while (true){
		std::cin >> startingposition;
		if (knight->startPath(startingposition.c_str())) break;
		std::cout << "the starting position you chose is not a square on the field the format is (letter)(number) example \"c8\"" << std::endl;
	}
	system("pause");
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
