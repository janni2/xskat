#include <SDL2/SDL.h>
#include <iostream>
#include "skat.h"
#include "core_utils.h"

extern "C" int run_sdl_ui(int argc, char* argv[]) {
    setrnd(&seed[0], time((time_t*)0));
    mischen();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "XSkat-SDL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < 10; ++i) {
                    SDL_Rect cardRect = { 50 + i * 70, 450, 60, 90 };
                    if (x >= cardRect.x && x <= cardRect.x + cardRect.w &&
                        y >= cardRect.y && y <= cardRect.y + cardRect.h) {
                        std::cout << "Clicked on card " << i << std::endl;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render player 0's hand
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < 10; ++i) {
            if (cards[i] != -1) {
                SDL_Rect cardRect = { 50 + i * 70, 450, 60, 90 };
                SDL_RenderFillRect(renderer, &cardRect);
            }
        }

        // Render player 1's hand
        for (int i = 0; i < 10; ++i) {
            if (cards[10 + i] != -1) {
                SDL_Rect cardRect = { 50, 50 + i * 30, 90, 60 };
                SDL_RenderFillRect(renderer, &cardRect);
            }
        }

        // Render player 2's hand
        for (int i = 0; i < 10; ++i) {
            if (cards[20 + i] != -1) {
                SDL_Rect cardRect = { 660, 50 + i * 30, 90, 60 };
                SDL_RenderFillRect(renderer, &cardRect);
            }
        }

        // Render Skat
        if (cards[30] != -1) {
            SDL_Rect cardRect = { 350, 50, 60, 90 };
            SDL_RenderFillRect(renderer, &cardRect);
        }
        if (cards[31] != -1) {
            SDL_Rect cardRect = { 420, 50, 60, 90 };
            SDL_RenderFillRect(renderer, &cardRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
