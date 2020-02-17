#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
class ENGINE_API TileMap
{
private:
	GLuint width;  //ancho en tiles
	GLuint height; //alto en tile
	GLuint tileWidth;//ancho del tile
	GLuint tileHeight;//alto del tile
	Tile* mapa[5][5];

public:
	TileMap(Renderer* render, Material* material, const char* bmpFile, int columns, int rows);
	~TileMap();
	void DrawTiles();
	void UpdateTilesAnim(float time);
};
#endif