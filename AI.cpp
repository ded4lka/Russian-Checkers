#include "AI.h"
#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

AI::AI(pc_color color, Table* table) : Player(color, table) {
	isPlayerHuman = false;
}

//recursive method to free memory allocated on a tree
void AI::clearTree(vector<AImove*>& tree) {
	for (vector<AImove*>::iterator i = tree.begin(); i != tree.end(); i++) {
		AImove* m = *i;
		if (m->next.size() != 0)
			clearTree(m->next);
		delete m;
	}
}

GameMove* AI::play() {
	// Create a list of possible moves
	vector<AImove*> moveList;
	vector<Piece>* myPieces = getPieces();

	// Iterate through all pieces to find their possible moves
	for (int i = 0; i < myPieces->size(); i++) {
		vector<AImove*> moves = possibleMovesForPiece(myPieces->at(i), NULL);
		moveList.insert(moveList.end(), moves.begin(), moves.end());
	}

	// Create minimax tree to analyze possible moves
	vector<AImove*> nowList = moveList;
	vector<AImove*> nextList;
	for (int i = 0; i < this->maxDepth - 1; i++) {
		// Iterate through each move in the current level
		for (int j = 0; j < nowList.size(); j++) {
			AImove* m = nowList[j];
			AITable& table = m->tableGame;
			vector<Piece>* myPieces = getPieces(table);
			// Generate new level of movements by iterating through pieces
			for (int k = 0; k < myPieces->size(); k++) {
				vector<AImove*> moves = possibleMovesForPiece(myPieces->at(k), m);
				nowList[j]->next.insert(nowList[j]->next.end(), moves.begin(), moves.end());
				nextList.insert(nextList.end(), moves.begin(), moves.end());
			}
		}
		// Move to the next level
		nowList = nextList;
		std::cout << "Level:" << i << " possibilities:" << nowList.size() << std::endl;
		nextList.clear();
	}

	// Find the best move using minimax algorithm
	GameMove* retMove = new GameMove();
	AImove* aiMove = getBestMove(moveList, 0, this->maxDepth);
	retMove->start = aiMove->m.start;
	retMove->end = aiMove->m.end;
	cout << "Size of list = " << moveList.size() << endl;

	// Clear the minimax tree to free memory
	this->clearTree(moveList);

	return retMove;
}

AImove* AI::getBestMove(vector<AImove*>& moveList, int layer, int maxLayer) {
	/////////////////////////////////////////
	//	Go through all layers and find min //
	//									   //
	//		__*__						   //
	//	   *     *   ------ layer 2		   //
	//	  / \   / \						   //
	//   *   * *   * ------ layer 3        //
	//									   //
	/////////////////////////////////////////
	if (layer == maxLayer - 1) {
		//if we are in the last level we calculate the minimum
		//and propagate it to the parent
		int min = INT_MAX;
		for (int j = 0; j < moveList.size(); j++) {
			if (moveList[j]->score < min)
				min = moveList[j]->score;
		}
		moveList[0]->previous->score += min;
		if (maxLayer != 1) {
			return NULL;
		}
	}
	else {
		//if we're not in the last level we need to propagate
		//the minimum calculation first
		for (int j = 0; j < moveList.size(); j++)
			getBestMove(moveList[j]->next, layer + 1, maxLayer);
		int min = INT_MAX;
		for (int j = 0; j < moveList.size(); j++) {
			if (moveList[j]->score < min)
				min = moveList[j]->score;
		}

		if (moveList[0]->previous != NULL)
			moveList[0]->previous->score += min;
	}

	if (layer == 0) {
		AImove* retMove = nullptr;
		int maxV = INT_MIN;
		for (int i = 0; i < moveList.size(); i++)
			if (moveList[i]->score > maxV) {
				maxV = moveList[i]->score;
				retMove = moveList[i];
			}
		return retMove;
	}
	return NULL;
}

AImove* AI::createTree(int treeDepth) {
	AImove* gameTree = nullptr;
	bool aiPlay = true;
	for (int i = 0; i < treeDepth; i++) {

		//vector<Piece> &pieces;


		//flip player
		aiPlay = !aiPlay;
	}

	return gameTree;
}

AI::~AI() {
	// TODO Auto-generated destructor stub

}

bool AI::checkPositionValid(position& p) {
	if (p.first >= 0 && p.first <= 7 &&
		p.second >= 0 && p.second <= 7)
		return true;
	return false;
}

void AI::click(int x, int y) {
	//does nothing for AI
	//but has to be declared anyway since it's
	//an virtual method of player
}

void AI::mouseMove(int x, int y) {


}

void AI::draw(SDL_Surface* screen) {

}

void AI::SDL2_draw(SDL_Renderer* renderer)
{

}