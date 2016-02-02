#include "Tile.h"


Tile::Tile(int x, int y, const char* name)
{	
	_x = x;
	_y = y;
	sprintf_s(_name, name);
	_visited = false;
}

Tile::Tile(){

}
Tile::~Tile()
{
}
