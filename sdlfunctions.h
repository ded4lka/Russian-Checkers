#pragma once

#include <SDL.h>
#include <string>

SDL_Surface* loadIMG(std::string); // Loads an image to the screen
void applySurface(int, int, SDL_Surface*, SDL_Surface*); // Applies image, but does not refresh screen
void FreeIMG(SDL_Surface*, ...); // Clears an image
