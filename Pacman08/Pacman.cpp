#include"Pacman.h"

Pacman::Pacman() {
	frame_ = 0;
	x_pos_ = 50;
	y_pos_ = 25;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	move.down_ = 0;
	move.left_ = 0;
	move.right_ = 0;
	move.up_ = 0;
	coins = 0;
}

Pacman :: ~Pacman() { ; }

// Để class Pacman sử dụng được hàm của lớp BaseObject, ta sử dụng từ khóa virtual
bool Pacman::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
	// Lấy giá trị chiều dài và chiều cao như dưới để xử lý va chạm
	if (ret == true) {
		width_frame_ = rect_.w / 6;
		height_frame_ = rect_.h;
	}

	return ret;
}

void Pacman::set_clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame_;
		frame_clip[0].h = height_frame_;

		frame_clip[1].x = width_frame_;
		frame_clip[1].y = 0;
		frame_clip[1].w = width_frame_;
		frame_clip[1].h = height_frame_;

		frame_clip[2].x = 2*width_frame_;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame_;
		frame_clip[2].h = height_frame_;

		frame_clip[3].x = 3*width_frame_;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame_;
		frame_clip[3].h = height_frame_;

		frame_clip[4].x = 4*width_frame_;
		frame_clip[4].y = 0;
		frame_clip[4].w = width_frame_;
		frame_clip[4].h = height_frame_;

		frame_clip[5].x = 5*width_frame_;
		frame_clip[5].y = 0;
		frame_clip[5].w = width_frame_;
		frame_clip[5].h = height_frame_;
 	}
}

void Pacman::Show(SDL_Renderer* des) {
	if (status_ == MOVE_LEFT) {
		LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/Pac1.png", des);
	}
	else if (status_ == MOVE_RIGHT) {
		LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/Pac.png", des);
	}
	else if (status_ == MOVE_UP) {
		LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/Pac2.png", des);
	}
	else {
		LoadImg("C:/Users/Admin/OneDrive/Desktop/GamePics/Pac3.png", des);
	}

	if (move.down_ == 1 || move.left_ == 1 || move.right_ == 1 || move.up_ == 1) {
		frame_++;
	}
	else {
		frame_ = 0;
	}

	if (frame_ >= 6) frame_ = 1;

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = &frame_clip[frame_];

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void Pacman::Action(SDL_Event events, SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
		case SDLK_LEFT: {
			status_ = MOVE_LEFT;
			move.down_ = 0;
			move.right_ = 0;
			move.up_ = 0;
			move.left_ = 1;
		}
					  break;
		case SDLK_RIGHT: {
			status_ = MOVE_RIGHT;
			move.left_ = 0;
			move.up_ = 0;
			move.down_ = 0;
			move.right_ = 1;
		}
					   break;
		case SDLK_UP: {
			status_ = MOVE_UP;
			move.down_ = 0;
			move.right_ = 0;
			move.left_ = 0;
			move.up_ = 1;
		}
					break;
		case SDLK_DOWN: {
			status_ = MOVE_DOWN;
			move.left_ = 0;
			move.right_ = 0;
			move.up_ = 0;
			move.down_ = 1;
		}
					  break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_LEFT: {
			move.left_ = 1;
		}
		break;
		case SDLK_RIGHT: {
			move.right_ = 1;
		}
		break;
		case SDLK_UP: {
			move.up_ = 1;
		}
		break;
		case SDLK_DOWN: {
			move.down_ = 1;
		}
		break;
		}
	}
}


void Pacman::Moving(Map& map_data) {
	
	x_val_ = 0;
	y_val_ = 0;
	if (move.left_ == 1) {
		x_val_ = x_val_ - pac_sp;
		//x_pos_ += x_val_;
	}
	if (move.right_ == 1) {
		x_val_ = x_val_ + pac_sp;
		//x_pos_ += x_val_;
	}
	if (move.down_ == 1) {
		y_val_ = y_val_ + pac_sp;
		//y_pos_ += y_val_;

	}
	if (move.up_ == 1) {
		y_val_ = y_val_ - pac_sp;
		//y_pos_ += y_val_;
	}
	Bound(map_data);
}

void Pacman::Bound(Map& map_data) {
	
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	
	
	int height_min_ = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_) / TILE_SIZE; 

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min_) / TILE_SIZE; 

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) {
			int v1 = map_data.tiles[y1][x2];
			int v2 = map_data.tiles[y2][x2];
			//cout << v1 << " " << v2 << "\n";
			if (v1 == 0 || v2 == 0) {
				map_data.tiles[y1][x2] = 3;
				map_data.tiles[y2][x2] = 3;
				//cout << map_data.tiles[y1][x2] << " " << map_data.tiles[y2][x2] << "\n";
				ManageCoins();
				//cout << coins << "\n";
			}
			else {
				if (map_data.tiles[y1][x2] == 1 || map_data.tiles[y2][x2] == 1) {
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;
				}
			}
		}
		else if (x_val_ < 0) {
			int v1 = map_data.tiles[y1][x1];
			int v2 = map_data.tiles[y2][x1];
			if (v1 == 0 || v2 == 0) {
				map_data.tiles[y1][x1] = 3;
				map_data.tiles[y2][x1] = 3;	
				ManageCoins();
			}
			else {
				if (map_data.tiles[y1][x1] == 1 || map_data.tiles[y2][x1] == 1) {
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
			}
		}
	}

	int width_min_ = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min_) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			int v1 = map_data.tiles[y2][x1];
			int v2 = map_data.tiles[y2][x2];
			if (v1 == 0 || v2 == 0) {
				map_data.tiles[y2][x1] = 3;
				map_data.tiles[y2][x2] = 3;
				ManageCoins();
			}
			else {
				if (map_data.tiles[y2][x1] == 1 || map_data.tiles[y2][x2] == 1) {
					y_pos_ = y2 * TILE_SIZE - height_frame_ - 1;
					y_val_ = 0;
				}
			}
		}
		else if (y_val_ < 0) {
			int v1 = map_data.tiles[y1][x1];
			int v2 = map_data.tiles[y1][x2];
			if (v1 == 0 || v2 == 0) {
				map_data.tiles[y1][x1] = 3;
				map_data.tiles[y1][x2] = 3;
				ManageCoins();
			}
			else 
			if (map_data.tiles[y1][x1] == 1 || map_data.tiles[y1][x2] == 1) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) x_pos_ = 0;
	else if (x_pos_ + width_frame_ > map_data.max_x_) 
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

}

void Pacman::ManageCoins() {
	coins++;
}

SDL_Rect Pacman::getRect() {
	SDL_Rect pac;
	pac.x = x_pos_;
	pac.y = y_pos_;
	pac.w = width_frame_;
	pac.h = height_frame_;
	return pac;
}