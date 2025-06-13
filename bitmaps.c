/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2000  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.

    Redistribution of modified versions is permitted
    provided that the following conditions are met:
    1. All copyright & permission notices are preserved.
    2.a) Only changes required for packaging or porting are made.
      or
    2.b) It is clearly stated who last changed the program.
         The program is renamed or
         the version number is of the form x.y.z,
         where x.y is the version of the original program
         and z is an arbitrary suffix.
*/

#define BITMAPS_C

#include "bitmaps.h" // Will include SDL.h and SDL_image.h

#include <stdio.h> // For fprintf

#include "skat.h" // For blatt[0] global variable

// These were for XBM, not used for GIF loading with SDL_image
// #define static
// #include "icon.xbm"
// #include "symbl.xbm"
// #include "symbs.xbm"
// #undef static

#include "cards.c" // This file contains the actual GIF byte arrays: e.g. unsigned char sa_gif[] = { ... };

SDL_Texture* get_card_texture_from_bitmaps(int card_id, SDL_Renderer* renderer) {
    if (!renderer) {
        fprintf(stderr, "Error: get_card_texture_from_bitmaps called with NULL renderer.\n");
        return NULL;
    }

    unsigned char* gif_data = NULL;
    size_t gif_size = 0;

    // card_id: -1 for back, 0-31 for faces.
    // Mapping to g_cardTextures: g_cardTextures[0] is back, g_cardTextures[1-32] are for card_id 0-31.

    if (card_id == -1) { // Card Back
        gif_data = back_gif;
        gif_size = sizeof(back_gif);
        // fprintf(stderr, "Debug: Loading card back (back_gif), size: %zu\n", gif_size);
    } else if (card_id >= 0 && card_id < 32) { // Face cards
        // Simplified mapping for demonstration.
        // This needs to be expanded to cover all cards based on blatt[0] and card_id.
        // The de_gif and fr_gif arrays are arrays of pointers. We need to map to the actual data arrays.

        // Example: Karo As (German: Eichel As, card_id 0 if suit 0 val 0)
        // Example: Pik 7 (German: Grün 7, card_id 8 if suit 1 val 0)
        // THIS IS A VERY SIMPLIFIED AND INCOMPLETE MAPPING
        if (blatt[0] >= 2) { // German deck examples
            if (card_id == 0)      { gif_data = ea_gif; gif_size = sizeof(ea_gif); } // Eichel As
            else if (card_id == 1) { gif_data = e10_gif; gif_size = sizeof(e10_gif);} // Eichel 10
            else if (card_id == 8) { gif_data = ga_gif; gif_size = sizeof(ga_gif); } // Grün As
            else if (card_id == 9) { gif_data = g10_gif; gif_size = sizeof(g10_gif); } // Grün 10
            else if (card_id == 16) { gif_data = ha_gif; gif_size = sizeof(ha_gif); } // Rot As
            else if (card_id == 17) { gif_data = h10_gif; gif_size = sizeof(h10_gif); } // Rot 10
            else if (card_id == 24) { gif_data = sa_gif; gif_size = sizeof(sa_gif); } // Schellen As
            else if (card_id == 25) { gif_data = s10_gif; gif_size = sizeof(s10_gif); } // Schellen 10
            else {
                 // fprintf(stderr, "Warning: No specific German card GIF mapped for ID %d.\n", card_id);
            }
        } else { // French deck examples (very simplified - French deck uses different value mapping for face cards)
            if (card_id == 0)      { gif_data = kak_gif; gif_size = sizeof(kak_gif); } // Karo Ass (example, actual mapping may vary)
            else if (card_id == 1) { gif_data = ka_gif; gif_size = sizeof(ka_gif); } // Karo 10 (example)
            // For French K, D, B, the fr_gif array is used.
            // Example: Pik Koenig (Spade King) - card_id might be 24 (suit 3) + value index for King
            // The fr_gif array indices are [suit][0=K, 1=D, 2=B]
            // Suit mapping: 0=Karo, 1=Herz, 2=Pik, 3=Kreuz
            else if (card_id == (2*8 + 2)) { gif_data = pik_gif; gif_size = sizeof(pik_gif); } // Pik Koenig (Pik is suit 2, K is value index 2 in fr_gif)
            else {
                // fprintf(stderr, "Warning: No specific French card GIF mapped for ID %d.\n", card_id);
            }
        }
    } else {
        fprintf(stderr, "Error: Invalid card_id %d requested in get_card_texture_from_bitmaps.\n", card_id);
        return NULL;
    }

    if (gif_data && gif_size > 0) {
        SDL_RWops* rw = SDL_RWFromConstMem(gif_data, gif_size);
        if (!rw) {
            fprintf(stderr, "Error: SDL_RWFromConstMem failed for card_id %d: %s\n", card_id, SDL_GetError());
            return NULL;
        }
        SDL_Texture* tex = IMG_LoadTexture_RW(renderer, rw, 1); // 1 to automatically free/close RWops
        if (!tex) {
            fprintf(stderr, "Error: IMG_LoadTexture_RW failed for card_id %d (%s): %s\n", card_id, "source_gif_name_placeholder", IMG_GetError());
        } else {
            // fprintf(stderr, "Debug: Successfully loaded texture for card_id %d.\n", card_id);
        }
        return tex;
    } else if (card_id != -1 && (card_id <0 || card_id >=32)){ // Avoid warning for unmapped cards unless it's an invalid ID
         // fprintf(stderr, "Warning: No GIF data or size for card_id %d.\n", card_id);
    } // else it's a valid card_id that just doesn't have a specific mapping above for this test.
    return NULL;
}
