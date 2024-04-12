#pragma once

#include <SDL.h>
#include "Table.h"
#include "Piece.h"
#include "Player.h"
#include "AI.h"
#include "Human.h"

class Game : Drawable {
private:
	Table table;
	int clickX, clickY;
	Player* player_white;
	Player* player_black;
	pc_color active_player;
public:

	Game();

	virtual ~Game();

	void draw(SDL_Surface* screen);

	// SDL2
	void SDL2_draw(SDL_Renderer* renderer);

	void click(int x, int y);

	void play();

	void mouseMove(int x, int y);
};