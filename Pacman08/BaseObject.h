#pragma once

#include"Commonfunc.h"

// Tải các hình ảnh lên màn hình: Ảnh -> Surface -> Textutre -> Màn hình.

/*
Mục đích:
- Tăng hiệu suất vẽ và hiển thị ảnh.
- Giúp thay đổi kích thước ảnh, hiển thị nhiều định dạng ảnh khác nhau và hỗ trợ xử lý hình ảnh
*/



// So sánh private và protected
class BaseObject {
protected:
	SDL_Texture* p_object_ = NULL;
	SDL_Rect rect_;
public:
	BaseObject();
	~BaseObject();
	virtual void Free();
	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; };
	SDL_Rect GetRect() const { return rect_; }

	// Tạo texture p_object_ (Ảnh -> Surface -> Texture)
	virtual bool LoadImg(std::string path, SDL_Renderer* screen = NULL);

	// Hiển thị texture p_object_ lên màn hình (Texture -> Màn hình)
	void Render(SDL_Renderer* des, SDL_Rect* clip = NULL);

};
