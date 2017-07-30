#ifndef CRANK_FLASHLIGHT_H
#define CRANK_FLASHLIGHT_H

#include <string>
#include <SDL.h>

class Graphics;

class Crank_Flashlight {
public:
	Crank_Flashlight();	
	/// <summary>
	/// Initializes a new instance of the <see cref="Crank_Flashlight"/> class.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="filepathOn">The filepath on.</param>
	/// <param name="filepathOff">The filepath off.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <param name="x">The x starting position.</param>
	/// <param name="y">The y starting position.</param>
	Crank_Flashlight(Graphics &graphics, const std::string &filepathOn, const std::string &filepathOff, int width, int height, int x, int y);
	~Crank_Flashlight();
	void draw(Graphics &graphics);
	void update(float elapsedTime);
	void crank(int energy);
private:
	// number of seconds the light will stay on before turning off
	int _life;
	//the amount of time that has elapsed
	float _timeElapsed;
	//the amount of work required to generate 1 new life in flashlight
	int _joule;
	int _generatedEnergy;

	SDL_Texture *_onTexture;
	SDL_Texture *_offTexture;
	SDL_Rect _sourceRect;
	SDL_Rect _destRect;
};

#endif // !CRANK_FLASHLIGHT_H
