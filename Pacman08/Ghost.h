#pragma once

#include"Commonfunc.h"

#include"BaseObject.h"

#include"Game_Map.h"


#define pac_sp 25;

class Ghost : public BaseObject {
public:
	Ghost(int x, int y);
	~Ghost();


	enum MoveType {
		MOVE_LEFT = 0, MOVE_RIGHT = 1, MOVE_UP = 2, MOVE_DOWN = 3
	};
	// Thêm thông số riêng cho kích thước tấm ảnh Pacman
	bool LoadImg(std::string path, SDL_Renderer* screen);
	// Hiển thị lên màn hình theo từng frame
	void Show(SDL_Renderer* des);
	// Hàm xử lý sự kiện
	void Action(SDL_Event events, SDL_Renderer* screen);
	// Tạo hiệu ứng animation cho biến SDL_Rect frame_clip[5] 
	void set_clips();
	// Di chuyển nhân vật 
	void Moving(Map& map_data);
	// Va chạm
	void Bound(Map& map_data);
	//void SetPos(int x, int y) { x = x_pos_; y = y_pos_; }
	SDL_Rect getRect();
private:
	int x_val_;
	int y_val_;

	int x_pos_;
	int y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip[2];
	Input_Move move;
	int frame_;
	int status_;
};
