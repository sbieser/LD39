#ifndef PLAYER_H
#define PLAYER_H

#include "animated_sprite.h"
#include "globals.h"

class Graphics;
struct SDL_Rect;

class Creep : public AnimatedSprite {
public:
	Creep();	
	/// <summary>
	/// Initializes a new instance of the <see cref="Creep"/> class.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="filepath">The file name of the sprite.</param>
	/// <param name="x">The x starting position.</param>
	/// <param name="y">The y starting position.</param>
	Creep(Graphics &graphics, const std::string &filePath, float destinationX, float destinationY);
	void draw(Graphics &graphics);
	void update(float elapsedTime);
	SDL_Rect bbox();
	void takeDamage(int amount);
	int life();
protected:
private:
	int _destinationX;
	int _destinationY;

	float _timeToUpdate;
	float _timeElapsed;
	float _speed;

	float _directionX;
	float _directionY;

	int _life;

	// Inherited via AnimatedSprite
	virtual void animationDone(std::string currentAnimation) override;

	// Inherited via AnimatedSprite
	virtual void setupAnimation() override;
};

#endif // !PLAYER_H
