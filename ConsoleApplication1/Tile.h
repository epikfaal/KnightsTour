#pragma once
#include <string>
class Tile
{
private:
	char _name[4];
	int _x, _y;
	bool _visited;
public:
	int getX(){ return _x; };
	int getY(){ return _y; };
	bool isVisited(){ return _visited; };
	const char* getName(){ return _name; };
	void setVisited(bool visited) { _visited = visited; };
	Tile(int x, int y, const char* name);
	Tile();
	~Tile();
};

