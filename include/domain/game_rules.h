/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

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

#ifndef DOMAIN_GAME_RULES_H
#define DOMAIN_GAME_RULES_H

/*
 * Domain Layer - Game Rules and Logic API
 * 
 * This header provides a unified interface to all game logic
 * implemented in the domain layer.
 */

// Null game variant rules and logic
#include "null.h"

/*
 * Future domain layer modules (when extracted):
 * 
 * #include "skat_rules.h"    // Core Skat game rules
 * #include "ramsch_rules.h"  // Ramsch variant rules (pure logic)
 * #include "card_logic.h"    // Card evaluation and comparison
 * #include "scoring.h"       // Game scoring calculations
 */

// Common game constants (could be moved to a separate file)
#define KREUZ   0
#define PIK     1  
#define HERZ    2
#define KARO    3
#define SIEBEN  0
#define ACHT    1
#define NEUN    2
#define ZEHN    3
#define BUBE    4
#define DAME    5
#define KOENIG  6
#define AS      7

/*
 * Domain Layer Architecture Notes:
 * 
 * The domain layer contains pure game logic that:
 * 1. Implements official Skat rules
 * 2. Has no dependencies on UI or external services
 * 3. Is deterministic and testable
 * 4. Can be used independently of the UI
 * 
 * Current state: Only null game logic is fully extracted.
 * Future: Extract more core game rules as pure functions.
 */

#endif /* DOMAIN_GAME_RULES_H */