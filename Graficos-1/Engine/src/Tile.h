#ifndef TILE_H
#define TILE_H
#include "Sprite.h"

class DLLEXPORT Tile : public Sprite
{
private:
	bool _walkable;
public:

	Tile(Renderer* render, int columns, int rows, bool walkable);
	~Tile();
	bool isWalkable();
	void setWalkable(bool walk);
};
#endif
