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

#ifndef APPLICATION_GAME_SERVICES_H
#define APPLICATION_GAME_SERVICES_H

/*
 * Application Layer - Game Services API
 * 
 * This header provides a unified interface to all business services
 * implemented in the application layer.
 */

// Core business services
#include "settings.h"      // Game settings and configuration
#include "text.h"          // Internationalization and localization
#include "irc.h"           // Network communication services
#include "ramsch.h"        // Ramsch game variant coordination

/*
 * Application Layer Services:
 * 
 * - Settings Service: Manages game configuration and player preferences
 * - Text Service: Handles internationalization and text localization
 * - IRC Service: Manages network communication and multiplayer coordination
 * - Ramsch Service: Coordinates Ramsch game variant business logic
 * 
 * Future services to consider:
 * - Game State Service: Manages overall game state persistence
 * - Player Service: Manages player profiles and statistics
 * - Tournament Service: Handles tournament mode and scoring
 * - AI Service: Coordinates computer player strategies
 */

/*
 * Application Layer Architecture Notes:
 * 
 * The application layer:
 * 1. Orchestrates business logic and services
 * 2. Coordinates between domain and UI layers
 * 3. Manages external dependencies (network, files)
 * 4. Handles cross-cutting concerns (i18n, settings)
 * 5. Provides services that the UI layer can consume
 */

#endif /* APPLICATION_GAME_SERVICES_H */