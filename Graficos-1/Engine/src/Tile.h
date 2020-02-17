//#ifndef TILE_H
//#define TILE_H
#pragma once
#include "Sprite.h"


class ENGINE_API Tile : public Sprite
{
private:
	bool _walkable;
public:

	Tile(Renderer* render, int columns, int rows);
	~Tile();
	bool isWalkable();
	void setWalkable(bool walk);
};
//#endif

