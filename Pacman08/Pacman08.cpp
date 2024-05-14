
#include"Commonfunc.h"

#include"BaseObject.h"

#include"Game_Map.h"

#include"Pacman.h"

#include"Ghost.h"

#include<vector>


BaseObject g_background;
TTF_Font* t_font;

bool Initdata() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;

	// Thiết lập chất lượng tỉ lệ vẽ của renderer trong SDL2.
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("LA_VI_ELM",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		success = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = false;
		else {
			SDL_SetRenderDrawColor(g_screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) {
				success = false;
			}
		}
	}
	return success;
}

bool loadBackground() {
	bool ret = g_background.LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/Background.png", g_screen);
	return ret;
}
int main(int argc, char* argv[]) {
	if (Initdata() == false)
		cout << "Fail to init SDL" << "\n";
	if (loadBackground() == false)
		cout << "Fail to load img\n";
	GameMap game_map;
	game_map.LoadMap();
	game_map.LoadTiles(g_screen);

	Pacman pac;
	pac.LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/Pac1.png", g_screen);
	pac.set_clips(); 

	Ghost g1(13 * 25, 10 * 25), g2(14 * 25, 10 * 25), g3(15 * 25, 10 * 25);
	g1.LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/PLeft.png", g_screen);
	g1.set_clips();
	g2.LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/PLeft.png", g_screen);
	g2.set_clips();
	g3.LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/PLeft.png", g_screen);
	g3.set_clips();

	bool is_quit = false;
	// Game loop
	while (!is_quit) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
			}
			pac.Action(g_event, g_screen);
			//g1.Action(g_event, g_screen);
			//g2.Action(g_event, g_screen);
			//g3.Action(g_event, g_screen);
			SDL_Delay(0);
		}
		SDL_SetRenderDrawColor(g_screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL);
		game_map.DrawMap(g_screen);
		Map& map_data = game_map.getMap();
		pac.Moving(map_data);
		pac.Show(g_screen);
		g1.Moving(map_data);
		g1.Show(g_screen);
		g2.Moving(map_data);
		g2.Show(g_screen);
		g3.Moving(map_data);
		g3.Show(g_screen);
		std::vector <Ghost> ghost_list;
		ghost_list.push_back(g1);
		ghost_list.push_back(g2);
		ghost_list.push_back(g3);
		for (int i = 0; i < 3; i++) {
			Ghost g = ghost_list[i];
			bool luv = false;
			luv = SDLCommonfunc::Va_Cham(pac.getRect(), ghost_list[i].getRect());
			if (luv) {
				pac.Free(); 
				if (MessageBox(NULL, L"You Lose!", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
					is_quit = true;
				}
	
			}
		}
		SDL_RenderPresent(g_screen);
		cout << pac.getCoins() << " ";
		if (pac.getCoins() == 292) {
			pac.Free();
			if (MessageBox(NULL, L"You win!", L"Congratulations!", MB_OK | MB_ICONSTOP) == IDOK) {
				is_quit = true;
			}
		}
		 SDL_Delay(125);
	    }
		 
	SDL_Quit();
	return 0;
}