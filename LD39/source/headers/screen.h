#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <SDL.h>

class Graphics;

class Screen {
public:
	Screen();
	Screen(Graphics &graphics, const std::string &filePath, int width, int height, int x, int y);
	~Screen();
	void draw(Graphics &graphics);
private:
	SDL_Rect _sourceRect;
	SDL_Rect _destRect;
	SDL_Texture *_texture;
};

#endif // !SCREEN_H

