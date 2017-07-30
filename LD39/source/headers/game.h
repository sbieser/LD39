#ifndef GAME_H
#define GAME_H

#include <vector>
#include "screen.h"
#include "crank_flashlight.h"
#include "creep.h"

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
	void update(float elapsedTime, Graphics & graphics);
	
	/// <summary>
	/// Sets the state.
	/// </summary>
	/// <param name="state">The state.</param>
	void setState(int state);

	Screen title_screen;
	Screen gameover_screen;
	Screen game_screen;
	Crank_Flashlight flashlight;
	
	//Lets have an array of creeps!
	//Creep creep;
	std::vector<Creep *> creeps;

	float _timeElapsed;
	float _randomTimeCreateCreep;

	int _state;
};

#endif // !GAME_H
