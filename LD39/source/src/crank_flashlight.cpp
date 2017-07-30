#include "crank_flashlight.h"
#include "graphics.h"

Crank_Flashlight::Crank_Flashlight()
{
}

Crank_Flashlight::Crank_Flashlight(Graphics & graphics, const std::string & filepathOn, const std::string & filepathOff, int width, int height, int x, int y)
{
	this->_onTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepathOn));
	this->_offTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepathOff));

	//this is correct
	this->_sourceRect = { x, y, width, height };
	
	this->_destRect = { x, y, width, height };
	this->_timeElapsed = 0;
	this->_life = 15;
	this->_joule = 4;
	this->_generatedEnergy = 0;
}

Crank_Flashlight::~Crank_Flashlight()
{
}

void Crank_Flashlight::draw(Graphics & graphics)
{
	//we can probably calculate where the flash light really is from SDL_GetMouseState
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Rect desinationRect = { mouseX - (this->_sourceRect.w / 2), mouseY - (this->_sourceRect.h / 2), this->_sourceRect.w, this->_sourceRect.h };
	if (_life > 0) {
		graphics.blitSurface(this->_onTexture, &this->_sourceRect, /*&this->_destRect*/&desinationRect);
	}
	else {
		graphics.blitSurface(this->_offTexture, &this->_sourceRect, &this->_destRect);
	}
}

void Crank_Flashlight::update(float elapsedTime)
{
	// this bit handles decreasing the life of a flashlight
	this->_timeElapsed += elapsedTime;
	//1000 ms is 1 second, decrease life of flashlight by 1 after each 1000 ms has passed by
	if (this->_timeElapsed > 2000) {
		this->_timeElapsed = 0;

		if (this->_life < -5) {
			//dont do anything for now??
		}
		else {
			this->_life -= 1;
		}
	}
}

void Crank_Flashlight::crank(int energy)
{
	this->_generatedEnergy += energy;
	if (this->_generatedEnergy > this->_joule) {
		this->_generatedEnergy = 0;
		this->_life += 1;
	}
}

