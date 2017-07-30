#include <cmath>
#include "creep.h"
#include "graphics.h"

Creep::Creep() {}

//AnimatedSprite::AnimatedSprite(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale, float timeToUpdate) :
Creep::Creep(Graphics &graphics, const std::string &filePath, float destinationX, float destinationY) : AnimatedSprite(graphics, filePath, 0, 0, 32, 32, 480, 320, 1, 200), _destinationX(destinationX), _destinationY(destinationY) {
	//not sure this is necessary
	
	this->setupAnimation();
	this->playAnimation("walk_front");

	this->_timeToUpdate = 100;
	this->_timeElapsed = 0;
	this->_speed = 2;

	float distance = std::sqrt(std::pow(this->_destinationX - this->_x, 2) + std::pow(this->_destinationY - this->_y, 2));
	this->_directionX = (this->_destinationX - this->_x) / distance;
	this->_directionY = (this->_destinationY - this->_y) / distance;

	this->_life = 3000;
}

void Creep::setupAnimation() {
	this->addAnimation(2, 32, 0, "walk_front", 32, 32, Vector2(0, 0));
	this->addAnimation(1, 0, 0, "idle_front", 32, 32, Vector2(0, 0));
}

void Creep::animationDone(std::string currentAnimation) {

}

void Creep::update(float elapsedTime) {

	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_timeToUpdate) {
		this->_timeElapsed = 0;
		this->_x += this->_directionX * this->_speed;
		this->_y += this->_directionY * this->_speed;
		this->_scale += .03f;
	}

	AnimatedSprite::update(elapsedTime);
}

SDL_Rect Creep::bbox()
{
	SDL_Rect destinationRectangle;
	destinationRectangle.x = this->_x;
	destinationRectangle.y = this->_y;
	destinationRectangle.w = this->_sourceRect.w * this->_scale;
	destinationRectangle.h = this->_sourceRect.h * this->_scale;

	return destinationRectangle;
}

void Creep::takeDamage(int amount)
{
	this->_life -= amount;
}

int Creep::life()
{
	return this->_life;
}

void Creep::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics);
}