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

#ifndef UI_PRESENTATION_H
#define UI_PRESENTATION_H

/*
 * UI Layer - Presentation Services API
 * 
 * This header provides a unified interface to all user interface
 * components implemented in the UI layer.
 */

// Core UI components  
#include "xio.h"       // X11 window management and event handling
#include "xdial.h"     // Dialog management and user interaction
#include "bitmaps.h"   // Graphics assets and card rendering

/*
 * UI Layer Components:
 * 
 * - Window Manager (xio): Handles X11 window creation, events, and display
 * - Dialog Manager (xdial): Manages user dialogs and input forms
 * - Graphics Manager (bitmaps): Handles card graphics and visual assets
 * 
 * Key Responsibilities:
 * - User input handling (mouse, keyboard)
 * - Visual presentation (cards, dialogs, menus)
 * - Event management and dispatching
 * - Screen layout and rendering
 */

/*
 * UI Layer Architecture Notes:
 * 
 * The UI layer:
 * 1. Handles all user interaction and visual presentation
 * 2. Uses X11 for windowing and graphics
 * 3. Coordinates with application layer for business logic
 * 4. Translates user actions into business events
 * 5. Presents game state through visual interfaces
 * 
 * Design principles:
 * - Separation of presentation from business logic
 * - Event-driven architecture for user interactions
 * - Modular components for different UI concerns
 */

#endif /* UI_PRESENTATION_H */