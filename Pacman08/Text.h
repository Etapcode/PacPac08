#pragma once

#include"Commonfunc.h" 

class Text {
public:
	Text();
	~Text();
	enum ColorText {
		RED = 0,
		WHITE = 1
	};
	bool LoadFromRendertext(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void SetCol(Uint8 red, Uint8 green, Uint8 blue);
	void SetCol(int type);
	void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	void SetText(const std::string& text) { text_ = text; }
	std::string GetText() const { return text_; }
private:
	std::string text_;
	SDL_Color col_text;
	SDL_Texture* texture_;
	int width;
	int height;
};