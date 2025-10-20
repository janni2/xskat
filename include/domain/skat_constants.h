/*
    XSkat Domain Layer - Game Constants
    Copyright (C) 2004  Gunter Gerhardt

    This file defines all magic numbers used throughout the XSkat codebase
    to improve code readability and maintainability.

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef SKAT_CONSTANTS_H
#define SKAT_CONSTANTS_H

/* ========================================================================
 * CARD DECK CONSTANTS
 * ======================================================================== */

// Total number of cards in a Skat deck
constexpr int TOTAL_CARDS = 32;

// Maximum card index (0-31)
constexpr int MAX_CARD_INDEX = 31;

// Number of cards per player (before skat exchange)
constexpr int CARDS_PER_PLAYER = 10;

// Number of cards in initial deal (including skat)
constexpr int CARDS_IN_INITIAL_DEAL = 12;

// Number of cards in the skat
constexpr int SKAT_SIZE = 2;

// Offset for skat cards in array
constexpr int SKAT_OFFSET = 20;

// Skat card positions in cards array
constexpr int SKAT_POSITION_1 = 30;
constexpr int SKAT_POSITION_2 = 31;

// Number of ranks per suit
constexpr int RANKS_PER_SUIT = 8;

// Number of suits
constexpr int NUM_SUITS = 4;

/* ========================================================================
 * CARD ENCODING BIT MASKS AND SHIFTS
 * ======================================================================== */

// Bit mask to extract card rank (lower 3 bits)
constexpr int CARD_RANK_MASK = 7;

// Bit shift to extract suit (upper bits)
constexpr int CARD_SUIT_SHIFT = 3;

// Bit mask for suit extraction in some contexts
constexpr int CARD_SUIT_MASK = 0x18;

/* ========================================================================
 * PLAYER CONSTANTS
 * ======================================================================== */

// Number of players in a Skat game
constexpr int NUM_PLAYERS = 3;

// Player position offsets
constexpr int LEFT_OFFSET = 1;
constexpr int RIGHT_OFFSET = 2;

/* ========================================================================
 * GAME PHASE AND TRICK CONSTANTS
 * ======================================================================== */

// Game types (trumpf values)
constexpr int GRAND_GAME = 4;
constexpr int RAMSCH_GAME = 5;

// Number of tricks in a complete game
constexpr int TOTAL_TRICKS = 11;

// Final trick number
constexpr int FINAL_TRICK = 9;

// Late game threshold (tricks remaining)
constexpr int LATE_GAME_TRICK = 7;
constexpr int VERY_LATE_GAME_TRICK = 8;

// Special trick numbers
constexpr int FIRST_TRICK = 1;
constexpr int SECOND_LAST_TRICK = 8;

// Two cards remaining for special situations
constexpr int TWO_CARDS_REMAINING = 2;

/* ========================================================================
 * SCORING CONSTANTS
 * ======================================================================== */

// Point thresholds for game outcomes
constexpr int SCHNEIDER_BOUNDARY = 30;
constexpr int GAME_WIN_POINTS = 60;
constexpr int GAME_WIN_THRESHOLD = 59;  // Greater than this wins
constexpr int SCHNEIDER_DECLARED_POINTS = 90;
constexpr int TOTAL_POINTS = 120;

// Bock event thresholds
constexpr int BOCK_MIN_VALUE_72 = 72;
constexpr int BOCK_MIN_VALUE_96 = 96;

// Ramsch and special scoring
constexpr int RAMSCH_GOOD_THRESHOLD = 44;

/* ========================================================================
 * TRUMP EVALUATION CONSTANTS
 * ======================================================================== */

// Minimum trump cards for various strategies
constexpr int MIN_TRUMPS_SAFE = 7;
constexpr int MIN_TRUMPS_WITH_ACES = 6;
constexpr int MIN_TRUMPS_MODERATE = 5;
constexpr int MIN_TRUMPS_RISKY = 4;
constexpr int MIN_TRUMPS_MINIMAL = 3;

// Jack (Bube) counts for decisions
constexpr int MIN_JACKS_FOR_RISK = 2;
constexpr int THREE_JACKS = 3;
constexpr int FOUR_JACKS = 4;

/* ========================================================================
 * BIDDING CONSTANTS
 * ======================================================================== */

// Standard bidding values
constexpr int REIZ_VALUE_17 = 17;
constexpr int REIZ_VALUE_18 = 18;

// Strategic calculation values
constexpr int MIN_TRUMP_CARDS_SAFE = 4;
constexpr int MIN_TRUMP_WITH_ACES = 5;
constexpr int MIN_DANGEROUS_KINGS_VALUE = 6;

// Point value calculations for bidding
constexpr int MIN_POINTS_FOR_BID_19 = 19;
constexpr int MIN_POINTS_FOR_BID_29 = 29;
constexpr int MIN_POINTS_FOR_BID_32 = 32;
constexpr int BASE_POINTS_39 = 39;

/* ========================================================================
 * AI STRATEGY CONSTANTS
 * ======================================================================== */

// Maximum cards in suit before ignoring
constexpr int MAX_SUIT_CARDS_TO_IGNORE = 3;

// Minimum trick value thresholds
constexpr int MIN_TRICK_VALUE = 3;
constexpr int MIN_TRICK_POINTS = 4;

// Card weight adjustments
constexpr int TEN_CARD_VALUE = 10;
constexpr int ADJUSTED_TEN_VALUE = 12;
constexpr int WEIGHT_MULTIPLIER = 2;
constexpr int TRUMP_WEIGHT_MODIFIER = 5;
constexpr int STRATEGIC_WEIGHT_MODIFIER = 6;

// Late game modifiers
constexpr int LATE_GAME_WEIGHT_MULTIPLIER = 2;
constexpr int LATE_GAME_TRUMP_BONUS = 12;
constexpr int LATE_GAME_SUIT_PENALTY = 7;
constexpr int LATE_GAME_ZEHN_BONUS = 6;

// Strategy penalties and bonuses
constexpr int NO_SUIT_BONUS = 8;
constexpr int LONG_SUIT_BONUS = 35;
constexpr int HIGH_CARD_PENALTY = 30;

/* ========================================================================
 * RANDOM STRATEGY THRESHOLDS
 * ======================================================================== */

// Random decision thresholds (used with rnd())
constexpr int RANDOM_THRESHOLD_1 = 1;
constexpr int RANDOM_THRESHOLD_3 = 3;
constexpr int RANDOM_THRESHOLD_7 = 7;
constexpr int RANDOM_ITERATIONS = 7;

/* ========================================================================
 * BUFFER AND ARRAY SIZES
 * ======================================================================== */

// Game list management
constexpr int MAX_GAME_LIST_SIZE = 360;
constexpr int GAME_LIST_TRIM_COUNT = 12;

// Buffer sizes for file I/O
constexpr int FILE_STRING_BUFFER_SIZE = 100;
constexpr int ERROR_READ_BUFFER_SIZE = 200;
constexpr int IRC_BUFFER_SIZE = 1024;

// Timing and delay constants
constexpr int MS_PER_DECISECOND = 100;
constexpr int INSTANT_PLAY_THRESHOLD = 101;
constexpr int DEFAULT_TRICK_DELAY = 7;
constexpr int MAX_TRICK_DELAY = 101;

/* ========================================================================
 * BOCK AND RAMSCH GAME CONSTANTS
 * ======================================================================== */

// Bock game cycle
constexpr int BOCK_CYCLE_LENGTH = 3;
constexpr int BOCK_WITH_RAMSCH = 2;
constexpr int RAMSCH_GAMES_COUNT = 3;

// Special trump counts
constexpr int EXCESSIVE_TRUMPS_THRESHOLD = 4;

/* ========================================================================
 * NULL GAME SPECIFIC CONSTANTS
 * ======================================================================== */

// Null game evaluation constants
constexpr int NULL_MAX_CARDS_FOR_EVAL = 40;
constexpr int NULL_SKAT_ARRAY_POS = 30;
constexpr int NULL_BONUS_64 = 64;

/* ========================================================================
 * CARD POSITION AND INDEX CONSTANTS
 * ======================================================================== */

// Hand size boundaries
constexpr int HAND_SIZE_MINUS_ONE = 9;
constexpr int LATE_TRICK_THRESHOLD = 7;

// Special card indices
constexpr int FIRST_PLAYER_START = 0;
constexpr int SECOND_PLAYER_START = 10;
constexpr int THIRD_PLAYER_START = 20;

/* ========================================================================
 * GRAND GAME CONSTANTS
 * ======================================================================== */

// Grand game evaluation thresholds
constexpr int GRAND_MIN_ACES = 2;
constexpr int GRAND_MIN_TENS = 1;
constexpr int GRAND_TOTAL_ACES = 4;
constexpr int GRAND_TOTAL_TENS = 4;
constexpr int GRAND_MIN_SUIT_LENGTH = 3;
constexpr int GRAND_GOOD_SUIT_LENGTH = 4;
constexpr int GRAND_STRONG_SUIT_LENGTH = 5;

/* ========================================================================
 * WAIT MODE CONSTANTS
 * ======================================================================== */

// Wait modes for timing
constexpr int WAIT_MODE_STANDARD = 0;
constexpr int WAIT_MODE_DELAY = 1;
constexpr int WAIT_MODE_TRICK = 2;

/* ========================================================================
 * SPECIAL GAME MECHANICS
 * ======================================================================== */

// Karo bube special logic
constexpr int KAROBUBE_TRUMP_COUNT = 2;
constexpr int KAROBUBE_IMPOSSIBLE = 9;

// Spitze evaluation
constexpr int SPITZE_MIN_TRUMPS_WITH_BB = 6;
constexpr int SPITZE_MIN_BB = 3;
constexpr int SPITZE_WITH_THREE_JACKS = 3;

/* ========================================================================
 * CARD COUNT THRESHOLDS
 * ======================================================================== */

// Various card counting thresholds for decisions
constexpr int SUIT_CARDS_SPARSE = 1;
constexpr int SUIT_CARDS_FEW = 2;
constexpr int SUIT_CARDS_MODERATE = 3;
constexpr int SUIT_CARDS_MANY = 4;
constexpr int SUIT_CARDS_FULL = 8;

// Gespielt (played cards) thresholds
constexpr int ALL_PLAYED = 2;
constexpr int NONE_PLAYED = 0;

#endif /* SKAT_CONSTANTS_H */
