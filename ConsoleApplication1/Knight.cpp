#include "Knight.h"


Knight::Knight()
{
	// Set current timestamp as the new random seed (required for placing the Knight at a random position)
	srand(time(NULL));

	// Create the board
	tilelist = new TileList();
	char letters[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	for (int x = 0; x < 8; x++){
		for (int y = 0; y < 8; y++){
			char name[4];
			sprintf_s(name, "%c%i", letters[y], x + 1);
			Tile* tempTile = new Tile(x, y, name);
			tilelist->grid[x][y] = tempTile;
			tilelist->list[((x * 8) + y)] = tempTile;
			printf("created tile ");
			printf(tilelist->list[((x * 8) + y)]->getName());
			printf("\n");
		}
	}

	// Place the Knight at a random position
	int field = 64;
	while (true){
		if (rand() % field == 0){
			currentTile = tilelist->list[field - 1];
			currentTile->setVisited(true);
			break;
		}
		field--;
	}
	movelist[0] = currentTile->getName();

	// Print the Knights starting location
	printf("The knight starts at ");
	printf(currentTile->getName());
	printf("\n");

	//start looking for moves
	/*int moves = findPossibleMoves();
	printf("Possible moves are: \n");
	for (int i = 0; i < moves; i++){
		printf(currentPossibleMoves[i]->getName());
		printf("\n");
	}*/
	while (true){
		loop();
		if (depth == 64){
			break;
		}
	}
	printf("yay we did it");
	for (int i = 0; i < 64; i++){
		printf("Move %i: %c \n", i, movelist[i]);
	}
}


Knight::~Knight()
{
}

int Knight::findPossibleMoves(){

	int possiblemoves = 0;
	int currentx = currentTile->getX();
	int currenty = currentTile->getY();

	if (currentx - 2 >= 0){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx - 2][currenty - 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 2][currenty - 1];
				possiblemoves++;
			}
		}
		if (currenty + 1 <= 7){
			if (!tilelist->grid[currentx - 2][currenty + 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 2][currenty + 1];
				possiblemoves++;
			}
		}
	}

	if (currentx + 2 <= 7){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx + 2][currenty - 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 2][currenty - 1];
				possiblemoves++;
			}
		}
		if (currenty + 1 <= 7){
			if (!tilelist->grid[currentx + 2][currenty + 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 2][currenty + 1];
				possiblemoves++;
			}
		}
	}

	if (currenty - 2 >= 0){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty - 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 1][currenty - 2];
				possiblemoves++;
			}
		}
		if (currentx + 1 <= 7){
			if (!tilelist->grid[currentx + 1][currenty - 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 1][currenty - 2];
				possiblemoves++;
			}
		}
	}

	if (currenty + 2 <= 7){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty + 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 1][currenty + 2];
				possiblemoves++;
			}
		}
		if (currentx + 1 <= 7){
			if (!tilelist->grid[currentx + 1][currenty + 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 1][currenty + 2];
				possiblemoves++;
			}
		}
	}
	return possiblemoves;
}

bool Knight::loop() {
	stepsrequired++;
	if (findPossibleMoves() > nextmove[depth]){
		makeMove(nextmove[depth]);
	}
	else {
		revertMove();
	}
	printf("step %i \n", stepsrequired);
	return true;
}

void Knight::makeMove(int moveNumber){
	movelist[depth] = currentTile->getName();
	nextmove[depth]++;
	depth++;
	currentTile = currentPossibleMoves[moveNumber];
	currentTile->setVisited(true);
}

void Knight::revertMove(){
	nextmove[depth] = 0;
	depth--;
	currentTile->setVisited(false);
	currentTile = tilelist->GetTileByName(movelist[depth]);
}