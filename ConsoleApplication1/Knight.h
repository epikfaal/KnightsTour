#pragma once
#include "tile.h"
#include <string>
#include <cstring>
#include <time.h>

struct TileList{
	int boardwidth, boardheight;
	Tile*** grid;
	Tile** list;
	Tile* GetTileByName(const char* name){
		int i = 0;
		while (true){
			if (strcmp(this->list[i]->getName(), name) == 0){
				return list[i];
			}
			i++;
			if (i == boardheight * boardwidth) return nullptr;
		}
	};
};
class Knight
{
	
private:
	int stepsrequired;
	int depth;
	struct TileList* tilelist;
	const char** movelist;
	int* nextmove;
	Tile* currentPossibleMoves[8];
	Tile* currentTile;
	bool tiedOptions;
	
	int findPossibleMoves(Tile* referenceTile);
	int fillPossibleMoves(); 
	void showDigitsInNumber(int* digits, int number);
	void sortMovesAscendingByScore(int* scorearray, int array);
	void makeMove(int moveNumber);
	void revertMove();
	bool loop();
	void printRow(int row);
public:
	bool initBoard(int width, int height);
	int startPath(const char* startingname);
	void printBoard();
	Knight();
	~Knight();
};

