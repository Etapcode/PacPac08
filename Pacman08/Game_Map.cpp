#include"Game_Map.h"

void GameMap::LoadMap() {
	FILE* fp = NULL;
	fopen_s(&fp , "C:/Users/Admin/OneDrive/Desktop/GamePics/map.txt", "r");
	if (fp == NULL) { cout << "Fail to open file\n"; return; }
	
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			// Ghi giá trị ( Các trạng thái của các điểm có tọa độ i, j trong file fp vào struct map
			fscanf_s(fp, "%d", &game_map.tiles[i][j]);
			if (j > game_map.max_x_) game_map.max_x_ = j;
			if (i > game_map.max_y_) game_map.max_y_ = i;
		}
		cout << "\n";
	}
	game_map.max_x_ = (game_map.max_x_ + 1)*TILE_SIZE;
	game_map.max_y_ = (game_map.max_y_ + 1)*TILE_SIZE;

	game_map.start_x_ = 0;
	game_map.start_y_ = 0;
	//game_map.file_name = name;
	fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen) {
	FILE* fp = NULL;
	fopen_s(&fp, "C:/Users/Admin/OneDrive/Desktop/GamePics/Wall_C.png", "r");
	if (fp == NULL) {
		cout << "Fail to load map\n";
	}
	fclose(fp);
	tile_map[0].LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/Wall_C.png", screen);
	tile_map[1].LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/gate.png", screen);
	tile_map[2].LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/dot.png", screen);
}

void GameMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int	y2 = 0;
	
	x1 = (game_map.start_x_ % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
	
	y1 = (game_map.start_y_ % TILE_SIZE)* -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
	int map_y = game_map.start_y_/TILE_SIZE;


	for (int i = y1; i < y2; i += TILE_SIZE) 
	{
		int map_x = game_map.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) 
		{
			int val = game_map.tiles[map_y][map_x];
			// cout << val << " ";
			if (val == 1) {
				tile_map[0].SetRect(j, i);
				tile_map[0].Render(screen);
			}
			else if (val == 2) {
				tile_map[1].SetRect(j, i);
				tile_map[1].Render(screen);
			}
			else if (val == 0) {
				tile_map[2].SetRect(j, i);
				tile_map[2].Render(screen);
			}
			map_x++;
		}
		cout << "\n";
		map_y++;
	}

}