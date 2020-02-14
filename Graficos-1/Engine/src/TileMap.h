#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
class DLLEXPORT TileMap
{
private:
	GLuint width;  //ancho en tiles
	GLuint height; //alto en tile
	GLuint tileWidth;//ancho del tile
	GLuint tileHeight;//alto del tile

public:
	TileMap();
	~TileMap();
};
#endif