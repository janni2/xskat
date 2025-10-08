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

#ifndef GAME_INTERFACES_H
#define GAME_INTERFACES_H

/* 
 * Layered Architecture Interfaces for XSkat
 * 
 * This header defines the contracts between architectural layers:
 * - Domain Layer: Pure game logic and rules
 * - Application Layer: Business services and coordination
 * - UI Layer: User interface and presentation
 */

// Domain Layer Interface - Pure Game Logic
// Functions that implement core Skat game rules without dependencies
#include "domain/null.h"

// Application Layer Interface - Business Services  
// Functions that coordinate game flow and manage application state
#include "application/settings.h"
#include "application/text.h"
#include "application/irc.h"
#include "domain/ramsch.h"

// UI Layer Interface - Presentation Services
// Functions that handle user interaction and display
#include "ui/xio.h"
#include "ui/xdial.h"  
#include "ui/bitmaps.h"

// Core Game Orchestration (main application)
// Coordinates all layers and manages overall game flow
#include "skat.h"

/*
 * Architecture Notes:
 * 
 * Domain Layer (src/domain/, include/domain/):
 * - Contains pure game logic and rules
 * - No dependencies on UI or external services
 * - Functions are deterministic and testable
 * 
 * Application Layer (src/application/, include/application/):
 * - Business logic and service coordination  
 * - Networking, internationalization, settings
 * - May depend on domain layer but not UI layer
 * 
 * UI Layer (src/ui/, include/ui/):
 * - User interface and presentation logic
 * - X11 window management, dialogs, graphics
 * - May depend on application and domain layers
 * 
 * Main Application (src/skat.c):
 * - Orchestrates all layers
 * - Contains main game loop and coordination logic
 * - Acts as the composition root
 */

#endif /* GAME_INTERFACES_H */