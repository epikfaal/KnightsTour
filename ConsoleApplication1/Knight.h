#pragma once
#include "tile.h"
#include <string>
#include <cstring>
#include <time.h>
/*struct TileList{
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
	
};*/
struct /*Variable*/TileList{
	Tile*** grid;
	Tile** list;
	Tile* GetTileByName(const char* name){
		int i = 0;
		while (true){
			if (strcmp(this->list[i]->getName(), name) == 0){
				return list[i];
			}
			i++;
		}
		return nullptr;
	};
};
class Knight
{
	
private:
	int stepsrequired;
	int depth;
	int boardwidth, boardheight;
	struct TileList* tilelist;
	//struct VariableTileList* vartilelist;
	const char** movelist;
	int* nextmove;
	Tile* currentPossibleMoves[8];
	Tile* currentTile;
	bool tiedOptions;
	bool boardinit = false;
	
	int findPossibleMoves(Tile* referenceTile);
	int fillPossibleMoves(); 
	void makeMove(int moveNumber);
	void revertMove();
	bool loop();
public:
	//void startPath(Tile startingtile);
	//bool startPath(int startingx, int startingy);
	bool initBoard(int width, int height);
	bool startPath(const char* startingname);
	void printBoard(int row);
	Knight();
	~Knight();
};

