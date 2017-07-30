#include <SDL.h>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
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

	//this->_state = 0;
	this->setState(0);
	this->game_screen = Screen(graphics, "content/backgrounds/better_background.png", 960, 640, 0, 0);
	this->title_screen = Screen(graphics, "content/backgrounds/title_screen.png", 960, 640, 0, 0);
	this->gameover_screen = Screen(graphics, "content/backgrounds/game_over.png", 960, 640, 0, 0);
	this->flashlight = Crank_Flashlight(graphics, "content/light/lighted_area.png", "content/light/light_off.png", 1920, 1280, 0, 0);
	 
	//this->creeps.push_back(new Creep(graphics, "content/sprites/creep_1.png", 480, 640));

	this->_randomTimeCreateCreep = (rand() % 10) * 1000;
	this->_timeElapsed = 0;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	bool z_pressed = false;

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
			if (this->_state == 0 || this->_state == 2) {
				this->setState(1);
			}
		}
		else if (input.wasKeyPressed(SDL_SCANCODE_Z) == true) {
			z_pressed = true;
		}
		else if (input.wasKeyPressed(SDL_SCANCODE_BACKSLASH) == true) {
			if (z_pressed) {
				z_pressed = false;
				this->flashlight.crank(2);
			}
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME), graphics);

		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {

	//clear the screen, prep to be ready to render more stuff
	graphics.clear();


	switch (this->_state) {
		case 0: {
			//title screen
			this->title_screen.draw(graphics);
			break;
		}
		case 1: {
			this->game_screen.draw(graphics);
			// Iterate and print values of vector
			for (Creep * creep : creeps) {
				creep->draw(graphics);
			}
			this->flashlight.draw(graphics);
			//we will do other draws here
			break;
		}
		case 2: {
			this->gameover_screen.draw(graphics);
			break;
		}
	}

	//this will take what is on the renderer and render it to the screen
	graphics.flip();
}

void Game::update(float elapsedTime, Graphics & graphics) {


	switch (this->_state) {
		case 0: {
			//do nothing
			break;
		}
		case 1: {

			//start
			this->flashlight.update(elapsedTime);

			//Query mouse events and figure stuff out like are we hurting the creeps?
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			//randomly generate creeps somehow??
			this->_timeElapsed += elapsedTime;
			if (this->_timeElapsed > this->_randomTimeCreateCreep) {

				//UPDATE MOVEMENT
				this->_timeElapsed = 0;
				int randSide = rand() % 4;
				int destinationX;
				int destinationY;
				if (randSide == 0) {
					//upper
					destinationX = rand() % 960;         // v1 in the range 0 to 99
					destinationY = 0;
				}
				else if (randSide == 1) {
					//lower
					destinationX = rand() % 960;
					destinationY = 640;
				}
				else if (randSide == 2) {
					//right
					destinationX = 960;
					destinationY = rand() % 640;
				}
				else {
					//left
					destinationX = 0;
					destinationY = rand() % 640;
				}

				this->creeps.push_back(new Creep(graphics, "content/sprites/creep_1.png", destinationX, destinationY));
				this->_randomTimeCreateCreep = (rand() % 15) * 1000;
			}
			//end


			//update the creeps
			std::vector<Creep *>::iterator iter;
			for (iter = this->creeps.begin(); iter != this->creeps.end(); ) {
				(*iter)->update(elapsedTime);

				SDL_Point mousePosition = { mouseX, mouseY };
				if (SDL_PointInRect(&mousePosition, &(*iter)->bbox())) {
					(*iter)->takeDamage(elapsedTime);
				}

				if (((*iter)->bbox().x + (*iter)->bbox().w)  > 960 || (*iter)->bbox().x < 0) {
					this->setState(2);
					break;
				}
				else if (((*iter)->bbox().y + (*iter)->bbox().h) > 640 || (*iter)->bbox().y < 0) {
					this->setState(2);
					break;
				}
				else if ((*iter)->life() < 0) {
					iter = this->creeps.erase(iter);
				}
				else {
					++iter;
				}
			}

			break;
		}
		case 2: {
			//do nothing
			break;
		}
	}
}

void Game::setState(int state)
{
	this->_state = state;
	if (this->_state == 2) {
		//clear the game state
		this->creeps.clear();
	}
}
