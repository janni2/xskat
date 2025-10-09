/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2024 Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef SKAT_ENUMS_H
#define SKAT_ENUMS_H

// Represents the four suits in a Skat deck.
typedef enum {
    SUIT_KREUZ,  // Clubs
    SUIT_PIK,    // Spades
    SUIT_HERZ,   // Hearts
    SUIT_KARO    // Diamonds
} Suit;

// Represents the ranks of cards in a Skat deck.
// The order is based on the original game's value mapping.
typedef enum {
    RANK_AS,
    RANK_ZEHN,
    RANK_KOENIG,
    RANK_DAME,
    RANK_BUBE,
    RANK_NEUN,
    RANK_ACHT,
    RANK_SIEBEN
} Rank;

#endif // SKAT_ENUMS_H