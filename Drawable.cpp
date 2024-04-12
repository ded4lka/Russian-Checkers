#include <SDL.h>
#include <SDL_image.h>
#include "Drawable.h"
#include <iostream>

using namespace std;

SDL_Surface* Drawable::screen;
SDL_Renderer* Drawable::renderer;

void Drawable::loadIMG(string filename, string id) {
    if (surfaces.find(id) != surfaces.end()) {
        cout << "Image " << id << " already loaded" << endl;
        return;
    }
    SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
    if (loadedSurface == NULL) {
        cout << SDL_GetError() << flush << endl;

    }
    surfaces[id] = loadedSurface;// optimizedSurface;
    return;
}

// SDL2
void Drawable::SDL2_loadIMG(string filename, string id)
{
    if (textures.find(id) != textures.end()) {
        cout << "Image " << id << " already loaded" << endl;
        return;
    }

    SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
    if (loadedSurface == nullptr) {
        cerr << "Error loading image: " << SDL_GetError() << endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (texture == nullptr) {
        cerr << "Error creating texture from surface: " << SDL_GetError() << endl;
        return;
    }

    textures[id] = texture;
}

void Drawable::applySurface(int x, int y, string id, SDL_Surface* destination) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    // Blit the surface:
    SDL_BlitSurface(surfaces[id], NULL, destination, &offset);
}

// SDL2
void Drawable::applyTexture(int x, int y, string id, SDL_Renderer* renderer)
{
    SDL_Rect destinationRect = { x, y, 0, 0 };
    SDL_QueryTexture(textures[id], NULL, NULL, &destinationRect.w, &destinationRect.h);
    SDL_RenderCopy(renderer, textures[id], NULL, &destinationRect);
}

Drawable::Drawable() {
    std::cout << "Calling drawable()." << std::endl << std::flush;
}

Drawable::~Drawable() {
    //clean memory
    for (map<string, SDL_Surface*>::iterator it = surfaces.begin(); it != surfaces.end(); it++) {
        if (it->second != NULL)
            SDL_FreeSurface(it->second);
    }

}
