#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "Knight.h"


int main(){
	int width, height;
	Knight* knight = new Knight();
	std::string startingposition;

	while (true){
		std::cout << "Please enter the boardwidth" << std::endl;
		std::cin >> width;
		std::cout << "Please enter the boardheight" << std::endl;
		std::cin >> height;
		if (width < 5 || height < 5){
			std::cout << "The boards width and height must at least be 5" << std::endl;
			continue;
		}
		else if ((width * height) % 2 == 1){
			std::cout << "The board size you have chosen has an odd number of squares, this means the Knight has to start at a black square e.g. a1 b2 c1 f6" << std::endl;
		}
		knight->initBoard(width, height);
	
	
		std::cout << "Please enter the knights starting position (type \"random\" for random)" << std::endl;
		
		std::cin >> startingposition;
		int response = knight->startPath(startingposition.c_str());
		if (response == 0) break;
		else if (response == 1)	std::cout << "the starting position you chose is not a square on the field the format is (letter)(number) example \"c8\"" << std::endl;
		else if (response == 2) std::cout << "The board has an odd size and the chosen starting position was a white square, therefore with the give parameters there is no knightstour possible" << std::endl;
	}
	knight->printBoard();
	system("pause");



}
