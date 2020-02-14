#include "Tile.h"

Tile::Tile(Renderer* render, int columns, int rows) : Sprite(render, columns, rows, 1.0f )
{
	_walkable = true;
}


Tile::~Tile()
{
}

bool Tile::isWalkable() {
	return _walkable;
}

void Tile::setWalkable(bool walk) {
	_walkable = walk;
}