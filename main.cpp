#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Drawable.h"
#include "sdlfunctions.h"
#include "Game.h"

#include <iostream>

using namespace std;

// Globals:
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const Uint32 fps = 40;
const Uint32 minframetime = 1000 / fps;

// Main:
int main(int argc, char* argv[]) {
    // Try to initialize SDL:
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL initialization failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Create the Window:
    window = SDL_CreateWindow("CheckersAI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    Drawable::renderer = renderer;



    // Загрузка первой текстуры
    SDL_Texture* texture1 = IMG_LoadTexture(renderer, "img/bpiece.png");
    if (texture1 == nullptr) {
        // Обработка ошибки загрузки текстуры
    }

    // Загрузка второй текстуры
    SDL_Texture* texture2 = IMG_LoadTexture(renderer, "img/wpiece.png");
    if (texture2 == nullptr) {
        // Обработка ошибки загрузки текстуры
    }

    SDL_RenderPresent(renderer);


    // Initialize SDL_image
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main game loop
    Game game;
    bool running = true;
    SDL_Event event;
    Uint32 frametime;

    while (running) {
        frametime = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                game.click(event.button.x, event.button.y);
            else if (event.type == SDL_MOUSEMOTION)
                game.mouseMove(event.motion.x, event.motion.y);
        }

        // Delay for FPS stability
        if (SDL_GetTicks() - frametime < minframetime)
            SDL_Delay(minframetime - (SDL_GetTicks() - frametime));

        // Game logic and drawing
        game.play();

        // Clear the renderer
        //SDL_RenderClear(renderer);

        game.SDL2_draw(renderer);

        // Render to screen
        SDL_RenderPresent(renderer);

        // Cap frame rate
        if (SDL_GetTicks() - frametime < minframetime)
            SDL_Delay(minframetime - (SDL_GetTicks() - frametime));
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
