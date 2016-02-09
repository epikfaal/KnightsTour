#pragma once
#include "tile.h"
#include <string>
#include <cstring>
#include <time.h>
struct TileList{
	Tile* grid[8][8];
	Tile* list[64];
	Tile* GetTileByName(const char* name){
		for (int i = 0; i < 64; i++){
			if(strcmp(this->list[i]->getName(), name) == 0){
				return list[i];
			}
		}
		return nullptr;
	};
	
};
class Knight
{
	
private:
	int stepsrequired;
	int depth;
	struct TileList* tilelist;
	const char* movelist[64];
	int nextmove[64];
	Tile* currentPossibleMoves[8];
	Tile* currentTile;
	bool tiedOptions;
	
	int findPossibleMoves(Tile* referenceTile);
	int fillPossibleMoves(); 
	void makeMove(int moveNumber);
	void revertMove();
	bool loop();
public:
	//void startPath(Tile startingtile);
	//bool startPath(int startingx, int startingy);
	bool startPath(const char* startingname);
	void printBoard(int row);
	Knight();
	~Knight();
};

