#pragma once

#include<iostream>

#include<windows.h>

#include<string>

#include<SDL.h>

#include<SDL_image.h>

#include<SDL_ttf.h> 

using namespace std;

// Các thông số cơ bản chung cần dùng	

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// Thông số màn hình hiển thị

const int SCREEN_WIDTH = 725;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

// Màu nền

const int COLOR_KEY_R = 167; 
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDERER_DRAW_COLOR = 255;

// Xây dựng kiểu map đặc trưng về vị trí, tọa độ.

const int TILE_SIZE = 25;

const int MAX_MAP_X = 29;

const int MAX_MAP_Y = 20;

struct Map {
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tiles[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name;
};

struct Input_Move {
	int left_;
	int right_;
	int up_;
	int down_;
};

namespace SDLCommonfunc {
	bool Va_Cham(const SDL_Rect& object1, const SDL_Rect& object2);
}




