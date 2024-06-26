#pragma once

#include "Player.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#include "AITable.h"

using namespace std;

#define POINT_KILL 1
#define POINT_KILL_KING 2
#define POINT_PROMOTE 3
class AImove {
public:
	GameMove m;

	int score;

	AImove* previous;

	vector<AImove*> next;

	AITable tableGame;

	AImove(position from, position to, int score, AImove* parent, AITable oTable);

};

class AI : public Player {
private:
	const int maxDepth = 4;
	bool checkPositionValid(position& p);
	void clearTree(vector<AImove*>& tree);
public:
	AI(pc_color color, Table* table);

	GameMove* play();

	void draw(SDL_Surface* screen);

	// SDL2
	void SDL2_draw(SDL_Renderer* renderer);

	void mouseMove(int x, int y);

	void click(int x, int y);

	virtual ~AI();

	std::vector<AImove*> possibleMovesForPiece(Piece& p, AImove* parent);

	AImove* createTree(int treeDepth);

	AImove* getBestMove(vector<AImove*>& moveList, int layer, int maxLayer);
};
