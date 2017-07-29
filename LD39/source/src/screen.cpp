#include "screen.h"
#include "graphics.h"

Screen::Screen()
{
}

Screen::Screen(Graphics & graphics, const std::string & filePath, int width, int height, int x, int y)
{
	this->_texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;
	this->_sourceRect.x = x;
	this->_sourceRect.y = y;

	this->_destRect = this->_sourceRect;
}

Screen::~Screen()
{
}

void Screen::draw(Graphics & graphics)
{
	graphics.blitSurface(this->_texture, &this->_sourceRect, &this->_destRect);
}
