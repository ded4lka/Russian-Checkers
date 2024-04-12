#include "Table.h"
#include <iostream>
#include <cmath>

using namespace std;

Table::Table() :Table(WHITE) {

}


//Table::Table(pc_color colorup) :TableBase(colorup) {
//	this->loadIMG("img/brownblock.bmp", "bblock");
//	this->loadIMG("img/whiteblock.bmp", "wblock");
//	this->loadIMG("img/bpiece.png", "bpiece");
//	this->loadIMG("img/wpiece.png", "wpiece");
//	this->loadIMG("img/crown.png", "crown");
//}

// SDL2
Table::Table(pc_color colorup) : TableBase(colorup)
{
	this->SDL2_loadIMG("img/brownblock.bmp", "texture_bblock");
	this->SDL2_loadIMG("img/whiteblock.bmp", "texture_wblock");
	this->SDL2_loadIMG("img/bpiece.png", "texture_bpiece");
	this->SDL2_loadIMG("img/wpiece.png", "texture_wpiece");
	this->SDL2_loadIMG("img/crown.png", "texture_crown");
}

Table::~Table() {
	// TODO Auto-generated destructor stub
}

void Table::draw(SDL_Surface* screen) {
	for (int i = 0; i < 8; i++) {
		bool inv = i % 2;
		for (int j = 0; j < 8; j++) {
			if (inv) {
				this->applySurface(i * 60, j * 60, "bblock", screen);
			}
			else {
				this->applySurface(i * 60, j * 60, "wblock", screen);
			}
			inv = !inv;
		}
	}

	for (int i = 0; i < this->pcBlack.size(); i++) {
		this->applySurface(pcBlack[i].getX() * 60, pcBlack[i].getY() * 60, "bpiece", screen);
		if (pcBlack[i].isKing()) {
			this->applySurface(pcBlack[i].getX() * 60, pcBlack[i].getY() * 60, "crown", screen);
		}
	}

	for (int i = 0; i < this->pcWhite.size(); i++) {
		this->applySurface(pcWhite[i].getX() * 60, pcWhite[i].getY() * 60, "wpiece", screen);
		if (pcWhite[i].isKing()) {
			this->applySurface(pcWhite[i].getX() * 60, pcWhite[i].getY() * 60, "crown", screen);
		}
	}
}

// SDL2
void Table::SDL2_draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < 8; i++) {
		bool inv = i % 2;
		for (int j = 0; j < 8; j++) {
			if (inv) {
				applyTexture(i * 60, j * 60, "texture_bblock", renderer);
			}
			else {
				applyTexture(i * 60, j * 60, "texture_wblock", renderer);
			}
			inv = !inv;
		}
	}

	for (int i = 0; i < this->pcBlack.size(); i++) {
		applyTexture(pcBlack[i].getX() * 60, pcBlack[i].getY() * 60, "texture_bpiece", renderer);
		if (pcBlack[i].isKing()) {
			applyTexture(pcBlack[i].getX() * 60, pcBlack[i].getY() * 60, "texture_crown", renderer);
		}
	}

	for (int i = 0; i < this->pcWhite.size(); i++) {
		applyTexture(pcWhite[i].getX() * 60, pcWhite[i].getY() * 60, "texture_wpiece", renderer);
		if (pcWhite[i].isKing()) {
			applyTexture(pcWhite[i].getX() * 60, pcWhite[i].getY() * 60, "texture_crown", renderer);
		}
	}
}