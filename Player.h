#pragma once

#include "Table.h"
#include "Drawable.h"

class Player : public Drawable {

protected:
	pc_color color;
	bool isPlayerHuman;
	Table* table;
public:
	Player(pc_color color, Table* table);

	virtual ~Player();

	virtual GameMove* play() = 0;

	virtual void click(int x, int y) = 0;

	virtual void mouseMove(int x, int y) = 0;

	virtual void draw(SDL_Surface* screen) = 0;

	// SDL2
	virtual void SDL2_draw(SDL_Renderer* renderer) = 0;

	pc_color getColor();

	vector<Piece>* getPieces();

	vector<Piece>* getPieces(TableBase& t);

	bool isHuman();
};
