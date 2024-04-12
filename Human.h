#pragma once

#include "Player.h"

class Human : public Player {
	position selected_case;
	bool selected;
	bool moveSelected;
	GameMove* moveToExecute;
public:
	Human(pc_color color, Table* table);

	GameMove* play();

	void draw(SDL_Surface* screen);

	// SDL2
	void SDL2_draw(SDL_Renderer* renderer);

	void click(int x, int y);

	void mouseMove(int x, int y);

	virtual ~Human();
};
