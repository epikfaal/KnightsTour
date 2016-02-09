#include "Knight.h"


Knight::Knight()
{
	// Set current timestamp as the new random seed (required for placing the Knight at a random position)
	srand(time(NULL));

	// Create the board
	/*tilelist = new TileList();
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
	}*/

	
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
		if (currenty + 1 < boardheight){
			if (!tilelist->grid[currentx - 2][currenty + 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 2][currenty + 1];
				possiblemoves++;
			}
		}
	}

	if (currentx + 2 < boardwidth){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx + 2][currenty - 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 2][currenty - 1];
				possiblemoves++;
			}
		}
		if (currenty + 1 < boardheight){
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
		if (currentx + 1 < boardwidth){
			if (!tilelist->grid[currentx + 1][currenty - 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 1][currenty - 2];
				possiblemoves++;
			}
		}
	}

	if (currenty + 2 < boardheight){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty + 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 1][currenty + 2];
				possiblemoves++;
			}
		}
		if (currentx + 1 < boardwidth){
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

	// set flag for tied options
	/*if (possiblemoves > nextmove[depth]){
		if (movepossibilities[nextmove[depth]] != movepossibilities[nextmove[depth] + 1]){
			tiedOptions = true;
		}
	}*/
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
		if (currenty + 1 < boardheight){
			if (!tilelist->grid[currentx - 2][currenty + 1]->isVisited()){
				possiblemoves++;
			}
		}
	}

	if (currentx + 2 < boardwidth){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx + 2][currenty - 1]->isVisited()){
				possiblemoves++;
			}
		}
		if (currenty + 1 < boardheight){
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
		if (currentx + 1 < boardwidth){
			if (!tilelist->grid[currentx + 1][currenty - 2]->isVisited()){
				possiblemoves++;
			}
		}
	}

	if (currenty + 2 < boardheight){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty + 2]->isVisited()){
				possiblemoves++;
			}
		}
		if (currentx + 1 < boardwidth){
			if (!tilelist->grid[currentx + 1][currenty + 2]->isVisited()){
				possiblemoves++;
			}
		}
	}
	return possiblemoves;
}


bool Knight::loop() {
	if (nextmove[depth] < 0) nextmove[depth] = 0;
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

	// if there are tied options, set nextmove to 9 so it won't explore aditional options
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
	size_t cols = boardwidth; // placeholder, will get boardwidth when it is customisable later
	size_t width = (cols * 5) + 1;
	char* dashedline;
	dashedline = (char*) malloc(width + 2); // the reason you need an extra byte is so you can specify the end of the string
	for (int i = 0; i < width; i++){
		dashedline[i] = '-' ;
	}
	dashedline[width] = '\n';
	dashedline[width + 1] = '\0';

	if (row == boardheight) printf(dashedline); // TODO switch 8 with number of rows
	

	printf("|");
	for (int i = 0; i < cols; i++){
		const char* name = tilelist->grid[i][row - 1]->getName();
		int movenumber;
		for (int j = 0; j < boardheight * boardwidth; j++){
			// reason we check like this is because they should both point to same string
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

bool Knight::startPath(const char* startingName){
	// Place the Knight at a random position
	if (strcmp(startingName, "random") == 0){
		int field = boardheight * boardwidth; 
		currentTile = tilelist->list[rand() % field];
	}
	else{
		currentTile = tilelist->GetTileByName(startingName);
		if (currentTile == nullptr){
			return false;
		}
	}

	currentTile->setVisited(true);
	movelist[0] = currentTile->getName();

	// Print the Knights starting location
	printf("The knight starts at ");
	printf(currentTile->getName());
	printf("\n");


	while (true){
		loop();
		if (depth == (boardheight * boardwidth) - 1) {
			movelist[depth] = currentTile->getName();
			break;
		}
	}
	printf("yay we did it\n");
	for (int i = 0; i < (boardheight * boardwidth) - 1; i++){
		printf("Move %i: ", i);
		printf(movelist[i]);
		printf("\n");
	}
	return true;
}

bool Knight::initBoard(int width, int height){
	printf("size of Tile**: %i\n", sizeof(Tile**));
	printf("size of Tile*: %i\n", sizeof(Tile*));
	printf("size of Tile: %i\n", sizeof(Tile));
	printf("size of int: %i\n", sizeof(int));
	printf("size of char: %i\n", sizeof(char));
	
	boardwidth = width;
	boardheight = height;

	nextmove = (int*)malloc(width * height * sizeof(int));
	int number = 0;
	while (number < width * height - 8){
		nextmove[number] = 0;
		number++;
	}
	nextmove[number] = 0;
	movelist = (const char**)malloc(width * height);

	tilelist = new TileList();

	tilelist->list = (Tile**)malloc(width * height * sizeof(Tile*));

	tilelist->grid = (Tile***) malloc(width * sizeof(Tile**));
	for (int i = 0; i < width; i++){
		tilelist->grid[i] = (Tile**)malloc(height * sizeof(Tile*));
	}

	
	char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	

	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			char name[4];
			sprintf_s(name, "%c%i", letters[y], x + 1);
			Tile* tempTile = new Tile(x, y, name);
			tilelist->grid[x][y] = tempTile;
			tilelist->list[((x * height) + y)] = tempTile;
			printf("created tile ");
			printf(tempTile->getName());
			printf("\n");
		}
	}
	boardinit = true;
	return true;
}