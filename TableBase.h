#pragma once

#include <vector>
#include "Piece.h"
#include <utility>
#include "Utils.h"

class GameMove {
public:
	position start;
	position end;
};

enum gameState { GAME_END, GAME_OK, GAME_POINT, GAME_INVALIDMOVE };

class TableBase {
private:
	bool removePiece(Piece* toRemove);
	void removeKilled(position& initial, position & final, pc_color pcolor);
	void checkPiecePromotion(Piece* p, position& to, pc_color pcolor);
public:
	vector<Piece> pcWhite, pcBlack;
	pc_color color_up; //check if white pieces are on the upper part

	TableBase();
	TableBase(pc_color colorup);
	virtual ~TableBase();
	pc_color getPlayerUp();
	Piece* getPiece(position p, pc_color color);
	gameState executeMove(position& from, position& to, pc_color pcolor);
	int isMoveValid(position& initial, position & final, pc_color pcolor);
	Piece* getPieceAt(position p);
};

