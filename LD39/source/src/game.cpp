#include <SDL.h>
#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"

/*
Game class
Holds all game loop information
*/

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameloop();
}

Game::~Game() {

}

void Game::gameloop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	this->screen = Screen(graphics, "content/backgrounds/test_bg.png", 640, 512, 0, 0);
	this->flashlight = Crank_Flashlight(graphics, "content/light/lighted_area.png", "content/light/light_off.png", 640, 512, 0, 0);

	int LAST_UPDATE_TIME = SDL_GetTicks();

	//start the game loop
	//one loop of this is one frame
	while (true) {
		
		//resets pressed and released keys
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		else if (input.wasKeyPressed(SDL_SCANCODE_SPACE) == true) {
			this->flashlight.crank(1);
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
		}
		else if (input.isKeyHeld(SDL_SCANCODE_SPACE) == true) {
			
		}
		else {
		}	

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {

	//clear the screen, prep to be ready to render more stuff
	graphics.clear();

	this->screen.draw(graphics);
	this->flashlight.draw(graphics);
	//we will do other draws here

	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}

void Game::update(float elapsedTime) {

	//1000 
	this->flashlight.update(elapsedTime);

}