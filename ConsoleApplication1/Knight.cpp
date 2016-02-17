#include "Knight.h"


Knight::Knight()
{
	// Set current timestamp as the new random seed (required for placing the Knight at a random position)
	srand(time(NULL));


	tilelist = new TileList();

	
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
		if (currenty + 1 < tilelist->boardheight){
			if (!tilelist->grid[currentx - 2][currenty + 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 2][currenty + 1];
				possiblemoves++;
			}
		}
	}

	if (currentx + 2 < tilelist->boardwidth){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx + 2][currenty - 1]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 2][currenty - 1];
				possiblemoves++;
			}
		}
		if (currenty + 1 < tilelist->boardheight){
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
		if (currentx + 1 < tilelist->boardwidth){
			if (!tilelist->grid[currentx + 1][currenty - 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 1][currenty - 2];
				possiblemoves++;
			}
		}
	}

	if (currenty + 2 < tilelist->boardheight){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty + 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx - 1][currenty + 2];
				possiblemoves++;
			}
		}
		if (currentx + 1 < tilelist->boardwidth){
			if (!tilelist->grid[currentx + 1][currenty + 2]->isVisited()){
				currentPossibleMoves[possiblemoves] = tilelist->grid[currentx + 1][currenty + 2];
				possiblemoves++;
			}
		}
	}

	// going to sort the array from least possible moves to most possible moves so it tries the least possible first according to Warnsdorf's rule
	int* movepossibilities = (int*)malloc(possiblemoves * sizeof(int));
	for (int i = 0; i < possiblemoves; i++){
		movepossibilities[i] = findPossibleMoves(currentPossibleMoves[i]);
	}

	// doing exchange sort for the array
	sortMovesAscendingByScore(movepossibilities, possiblemoves);

	// set flag for tied options
	if (possiblemoves > nextmove[depth]){
		if (movepossibilities[nextmove[depth]] != movepossibilities[nextmove[depth] + 1] && movelist[nextmove[depth]] !=0){
			tiedOptions = true;
		}
	}
	return possiblemoves;
}

void Knight::sortMovesAscendingByScore(int* scorearray, int arraylength){
	for (int i = 0; i < arraylength - 1; i++){
		for (int j = i + 1; j < arraylength; j++){
			if (scorearray[i] > scorearray[j]){

				int temp = scorearray[i];
				scorearray[i] = scorearray[j];
				scorearray[j] = temp;

				Tile* tempTile = currentPossibleMoves[i];
				currentPossibleMoves[i] = currentPossibleMoves[j];
				currentPossibleMoves[j] = tempTile;
			}
		}
	}
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
		if (currenty + 1 < tilelist->boardheight){
			if (!tilelist->grid[currentx - 2][currenty + 1]->isVisited()){
				possiblemoves++;
			}
		}
	}

	if (currentx + 2 < tilelist->boardwidth){
		if (currenty - 1 >= 0){
			if (!tilelist->grid[currentx + 2][currenty - 1]->isVisited()){
				possiblemoves++;
			}
		}
		if (currenty + 1 < tilelist->boardheight){
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
		if (currentx + 1 < tilelist->boardwidth){
			if (!tilelist->grid[currentx + 1][currenty - 2]->isVisited()){
				possiblemoves++;
			}
		}
	}

	if (currenty + 2 < tilelist->boardheight){
		if (currentx - 1 >= 0){
			if (!tilelist->grid[currentx - 1][currenty + 2]->isVisited()){
				possiblemoves++;
			}
		}
		if (currentx + 1 < tilelist->boardwidth){
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

	// if there are no tied options, set nextmove to 9 so it won't explore aditional options reduces 5x5 board starting position b4 from 682 to 54 steps
	if (tiedOptions) nextmove[depth] = 9;
	depth++;
	//printBoard();
	currentTile = currentPossibleMoves[moveNumber];
	currentTile->setVisited(true);
	//printf("The knight moves to ");
	//printf(currentTile->getName());
	//printf("\n");
}

void Knight::revertMove(){
	nextmove[depth] = 0;
	depth--;
	currentTile->setVisited(false);
	currentTile = tilelist->GetTileByName(movelist[depth]);
	//printf("The knight moves back to ");
	//printf(currentTile->getName());
	//printf("\n");
}

// print the board, this is a stupid teacher requirement, you can ignore if you want (adviced)
void Knight::printBoard(){
	
	for (int i = tilelist->boardheight; i > 0; i--)	printRow(i); 

}

void Knight::showDigitsInNumber(int* digits, int number){
	if (number > 9) showDigitsInNumber(digits, number / 10);
	*digits = *digits + 1; // *digits++ didn't work
}

// print a single row of the board
void Knight::printRow(int row){
	int cols = tilelist->boardwidth; 
	int digits = 0;
	showDigitsInNumber(&digits, tilelist->boardheight * tilelist->boardwidth);
	int width = (cols * (3 + digits)) + 1;

	char* dashedline;
	dashedline = (char*)malloc(width + 2); // the reason you need an extra byte is so you can specify the end of the string
	for (int i = 0; i < width; i++){
		dashedline[i] = '-';
	}
	dashedline[width] = '\n';
	dashedline[width + 1] = '\0';

	if (row == tilelist->boardheight) printf(dashedline); 


	printf("|");
	for (int i = 0; i < cols; i++){
		const char* name = tilelist->grid[i][row - 1]->getName();
		int movenumber;
		for (int j = 0; j < /*tilelist->boardheight * tilelist->boardwidth*/depth; j++){
			// reason we check like this is because they should both point to same string
			if (movelist[j] == name){
				movenumber = j;
				break;
			}
			movenumber = 99;
		};
		printf(" ");
		int movedigits = 0;
		showDigitsInNumber(&movedigits, movenumber);
		for (movedigits; movedigits < digits; movedigits++){
			printf("0");
		}
		printf("%i |", movenumber);
	}
	printf("\n");
	printf(dashedline);

	delete dashedline;
}

int Knight::startPath(const char* startingName){
	// Place the Knight at a random position
	if (strcmp(startingName, "random") == 0){
		int field = tilelist->boardheight * tilelist->boardwidth;
		currentTile = tilelist->list[rand() % field];
		while ((tilelist->boardheight * tilelist->boardwidth % 2) == 1){
			if ((currentTile->getX() + currentTile->getY()) % 2 == 1){
				currentTile = tilelist->list[rand() % field];
			}
			else {
				break;
			}
		}
	}
	else{
		currentTile = tilelist->GetTileByName(startingName);
		if (currentTile == nullptr){
			return 1;
		}
	}
	if ((currentTile->getX() + currentTile->getY()) % 2 == 1 && (tilelist->boardheight * tilelist->boardwidth % 2) == 1){
		return 2;
	}

	currentTile->setVisited(true);
	movelist[0] = currentTile->getName();

	// Print the Knights starting location
	printf("The knight starts at ");
	printf(currentTile->getName());
	printf("\n");


	while (true){
		loop();
		if (depth == (tilelist->boardheight * tilelist->boardwidth) - 1) {
			movelist[depth] = currentTile->getName();
			break;
		}
	}
	printf("yay we did it\n");
	for (int i = 0; i < (tilelist->boardheight * tilelist->boardwidth) - 1; i++){
		printf("Move %i: ", i);
		printf(movelist[i]);
		printf("\n");
	}
	return 0;
}

bool Knight::initBoard(int width, int height){
	
	tilelist->boardwidth = width;
	tilelist->boardheight = height;

	nextmove = (int*)malloc(width * height * sizeof(int));
	int number = 0;
	while (number < width * height - 8){
		nextmove[number] = 0;
		number++;
	}
	nextmove[number] = 0;
	movelist = (const char**)malloc(width * height * sizeof(const char*));


	tilelist->list = (Tile**)malloc(width * height * sizeof(Tile*));

	tilelist->grid = (Tile***) malloc(width * sizeof(Tile**));
	for (int i = 0; i < width; i++){
		tilelist->grid[i] = (Tile**)malloc(height * sizeof(Tile*));
	}

	
	char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	

	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			char name[4];
			sprintf_s(name, "%c%i", letters[x], y + 1);
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