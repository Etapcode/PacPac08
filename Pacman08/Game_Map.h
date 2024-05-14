#pragma once

#pragma warning(disable:4996)

#include"Commonfunc.h"

#include"BaseObject.h"

const int MAX_TILES_TYPE = 6;

class TileMap : public BaseObject {
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap {
public:
	GameMap() { ; }
	~GameMap() { ; }

	// Đọc file map text
	void LoadMap();
	// Load ảnh cho từ từng loại tile_map
	void LoadTiles(SDL_Renderer* screen);
	// Đặt hình ảnh vào các vị trí
    void DrawMap(SDL_Renderer* screen);
	Map& getMap() { return game_map; };
private:
	Map game_map;
	TileMap tile_map[3];
};
