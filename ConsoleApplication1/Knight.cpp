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
	int field = 64; // TODO change 64 with board size once that is customizable
	currentTile = tilelist->list[rand() % field];
	currentTile->setVisited(true);
	movelist[0] = currentTile->getName();

	// Print the Knights starting location
	printf("The knight starts at ");
	printf(currentTile->getName());
	printf("\n");


	while (true){
		loop();
		if (depth == 63){
			movelist[depth] = currentTile->getName();
			break;
		}
	}
	printf("yay we did it\n");
	for (int i = 0; i < 63; i++){
		printf("Move %i: ", i);
		printf(movelist[i]);
		printf("\n");
	}
}


Knight::~Knight()
{
}

int Knight::fillPossibleMoves(){
	tiedOptions = false;
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

	// going to sort the array from least possible moves to most possible moves so it tries the least possible first according to Warnsdorf's rule
	int movepossibilities[8];
	for (int i = 0; i < possiblemoves; i++){
		movepossibilities[i] = findPossibleMoves(currentPossibleMoves[i]);
	}
	// doing exchange sort for the array
	for (int i = 0; i < possiblemoves - 1; i++){
		for (int j = i + 1; j < possiblemoves; j++){
			if (movepossibilities[i] > movepossibilities[j]){

				int temp = movepossibilities[i];
				movepossibilities[i] = movepossibilities[j];
				movepossibilities[j] = temp;

				Tile* tempTile = currentPossibleMoves[i];
				currentPossibleMoves[i] = currentPossibleMoves[j];
				currentPossibleMoves[j] = tempTile;
			}
		}
	}
	//if there are no ties set nextmove to 9 so the other paths from this point will not be explored
	if (possiblemoves > nextmove[depth]){
		if (movepossibilities[nextmove[depth]] != movepossibilities[nextmove[depth] + 1]){
			tiedOptions = true;
		}
	}
	return possiblemoves;
}

int Knight::findPossibleMoves(Tile* referenceTile){

	int possiblemoves = 0;
	int currentx = referenceTile->getX();
	int currenty = referenceTile->getY();

	if (currentx - 2 >= 0){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx - 2][currenty - 1]->isVisited()){
				possiblemoves++;
			}
		}
		if (currenty + 1 <= 7){
			if (!tilelist->grid[currentx - 2][currenty + 1]->isVisited()){
				possiblemoves++;
			}
		}
	}

	if (currentx + 2 <= 7){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx + 2][currenty - 1]->isVisited()){
				possiblemoves++;
			}
		}
		if (currenty + 1 <= 7){
			if (!tilelist->grid[currentx + 2][currenty + 1]->isVisited()){
				possiblemoves++;
			}
		}
	}

	if (currenty - 2 >= 0){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty - 2]->isVisited()){
				possiblemoves++;
			}
		}
		if (currentx + 1 <= 7){
			if (!tilelist->grid[currentx + 1][currenty - 2]->isVisited()){
				possiblemoves++;
			}
		}
	}

	if (currenty + 2 <= 7){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty + 2]->isVisited()){
				possiblemoves++;
			}
		}
		if (currentx + 1 <= 7){
			if (!tilelist->grid[currentx + 1][currenty + 2]->isVisited()){
				possiblemoves++;
			}
		}
	}
	return possiblemoves;
}


bool Knight::loop() {
	stepsrequired++;
	if (fillPossibleMoves() > nextmove[depth]){
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
	if (tiedOptions) nextmove[depth] = 9;
	depth++;
	currentTile = currentPossibleMoves[moveNumber];
	currentTile->setVisited(true);
	printf("The knight moves to ");
	printf(currentTile->getName());
	printf("\n");
}

void Knight::revertMove(){
	nextmove[depth] = 0;
	depth--;
	currentTile->setVisited(false);
	currentTile = tilelist->GetTileByName(movelist[depth]);
	printf("The knight moves back to ");
	printf(currentTile->getName());
	printf("\n");
}

// print the board, this is a stupid teacher requirement, you can ignore if you want (adviced)
void Knight::printBoard(int row){
	size_t cols = 8; // placeholder, will get boardwidth when it is customisable later
	size_t width = (cols * 5) + 1;
	char* dashedline;
	dashedline = (char*) malloc(width + 2); // the reason you need an extra byte is so you can specify the end of the string
	for (int i = 0; i < width; i++){
		dashedline[i] = '-' ;
	}
	dashedline[width] = '\n';
	dashedline[width + 1] = '\0';

	if (row == 8) printf(dashedline); // TODO switch 8 with number of rows
	

	printf("|");
	for (int i = 0; i < cols; i++){
		const char* name = tilelist->grid[row - 1][i]->getName();
		int movenumber;
		for (int j = 0; j < 64; j++){
			if (movelist[j] == name){
				movenumber = j;
				break;
			}
		};
		if (movenumber > 9){
			printf(" %i |", movenumber);
		}
		else {
			if (movenumber == 0){
				printf(" XX |");
			}
			else {
				printf(" 0%i |", movenumber);
			}
		}
	}
	printf("\n");
	printf(dashedline);

	delete dashedline;
}