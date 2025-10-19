#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "skat.h"
#include "core_utils.h"
#include "ui/bitmaps.h"

// Maps the internal card representation to the corresponding image file.
// This allows for easy loading of card textures based on the game's logic.
const char* get_card_filename(int card_index) {
    static std::string filename;
    const char* suits[] = {"clubs", "spades", "hearts", "diamonds"};
    const char* ranks[] = {"A", "10", "K", "Q", "J", "09", "08", "07"};

    int suit = card_index >> 3;
    int rank = card_index & 7;

    filename = "resources/cards/card_";
    filename += suits[suit];
    filename += "_";
    filename += ranks[rank];
    filename += ".png";

    return filename.c_str();
}

// Loads all card textures from the filesystem into an array.
// This function initializes the graphical representation of the cards for rendering.
void load_card_textures(SDL_Renderer* renderer, SDL_Texture* card_textures[32]) {
    for (int i = 0; i < 32; ++i) {
        const char* filename = get_card_filename(i);
        SDL_Surface* surface = IMG_Load(filename);
        if (!surface) {
            std::cerr << "Failed to load image: " << filename << " - " << IMG_GetError() << std::endl;
            continue;
        }
        card_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

int sdl_main(int argc, char* argv[]) {
    SDL_Texture* card_textures[32] = {nullptr};
    SDL_Texture* back_texture = nullptr;
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

    load_card_textures(renderer, card_textures);
    SDL_Surface* back_surface = IMG_Load("resources/cards/card_back.png");
    if (back_surface) {
        back_texture = SDL_CreateTextureFromSurface(renderer, back_surface);
        SDL_FreeSurface(back_surface);
    } else {
        std::cerr << "Failed to load card back texture: " << IMG_GetError() << std::endl;
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
        for (int i = 0; i < 10; ++i) {
            int card_idx = cards[i];
            if (card_idx != -1) {
                SDL_Rect cardRect = { 50 + i * 70, 450, 60, 90 };
                SDL_RenderCopy(renderer, card_textures[card_idx], NULL, &cardRect);
            }
        }

        // Render player 1's hand
        for (int i = 0; i < 10; ++i) {
            int card_idx = cards[10 + i];
            if (card_idx != -1) {
                SDL_Rect cardRect = { 50, 50 + i * 30, 90, 60 };
                 SDL_RenderCopy(renderer, back_texture, NULL, &cardRect);
            }
        }

        // Render player 2's hand
        for (int i = 0; i < 10; ++i) {
            int card_idx = cards[20 + i];
            if (card_idx != -1) {
                SDL_Rect cardRect = { 660, 50 + i * 30, 90, 60 };
                SDL_RenderCopy(renderer, back_texture, NULL, &cardRect);
            }
        }

        // Render Skat
        int skat1_idx = cards[30];
        if (skat1_idx != -1) {
            SDL_Rect cardRect = { 350, 50, 60, 90 };
            SDL_RenderCopy(renderer, card_textures[skat1_idx], NULL, &cardRect);
        }
        int skat2_idx = cards[31];
        if (skat2_idx != -1) {
            SDL_Rect cardRect = { 420, 50, 60, 90 };
            SDL_RenderCopy(renderer, card_textures[skat2_idx], NULL, &cardRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
