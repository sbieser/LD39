#ifndef GAME_H
#define GAME_H

#include "screen.h"
#include "crank_flashlight.h"

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	/// <summary>
	/// The main game loop
	/// </summary>
	void gameloop();

	/// <summary>
	/// Draws the specified graphics.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	void draw(Graphics &graphics);

	/// <summary>
	/// Nothing  currently
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(float elapsedTime);

	Screen screen;
	Crank_Flashlight flashlight;
};

#endif // !GAME_H
