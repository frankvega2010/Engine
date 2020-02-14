#include "Tilemap.h"



TileMap::TileMap(Renderer* render, Material* material, const char* bmpFile, int columns, int rows)
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			mapa[i][j] = new Tile(render, columns, rows);
			mapa[i][j]->SetMaterial(material);
			mapa[i][j]->LoadMaterial(bmpFile,true);
			mapa[i][j]->SetPos(1 + (2.0f * i), 1 + (2.0f * j), 0);
			mapa[i][j]->SetAnim(0, 0, 0.0f);
		}
	}
}


TileMap::~TileMap()
{
}

 void TileMap::DrawTiles()
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			mapa[i][j]->Draw();
		}
	}
}

void TileMap::UpdateTilesAnim(float time)
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			mapa[i][j]->UpdAnim(time);
		}
	}
}