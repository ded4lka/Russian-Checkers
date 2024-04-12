#pragma once

#include <string>
#include <map>
#include <SDL.h>

using namespace std;

class Drawable {

private:
	map<string, SDL_Surface*> surfaces;
	
	// SDL2
	map<string, SDL_Texture*> textures;

public:

	static SDL_Surface* screen;
	static SDL_Renderer* renderer;

	Drawable();

	virtual void draw(SDL_Surface* screen) = 0;

	//SDL2
	virtual void SDL2_draw(SDL_Renderer* renderer) = 0;

	void loadIMG(string filename, string id);

	//SDL2
	void SDL2_loadIMG(string filename, string id);

	void applySurface(int x, int y, string id, SDL_Surface* destination);

	// SDL2
	void applyTexture(int x, int y, string id, SDL_Renderer* destination);

	virtual ~Drawable();
};
