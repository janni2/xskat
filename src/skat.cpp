
/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    XSkat Main Application - Layered Architecture Composition Root

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

    Architecture Overview:
    This file serves as the composition root and main orchestrator for the
    layered architecture implementation of XSkat.
*/

#define SKAT_C

#include "skat.h"

// Standard library includes
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Layered architecture interfaces
#include "game_interfaces.h"          // Unified layer interfaces
#include "core_utils.h"               // Core utility functions
#include "application/file_manager.h" // File I/O and configuration
#include "application/ai_engine.h"    // AI and computer player logic
#include "application/game_engine.h"  // Game coordination and flow management

/*
 * Layered Architecture Structure:
 * 
 * Domain Layer (src/domain/, include/domain/):
 * - Pure game logic and rules implementation
 * - No external dependencies, fully testable
 * 
 * Application Layer (src/application/, include/application/):
 * - Business services and coordination logic
 * - Settings, internationalization, networking
 * 
 * UI Layer (src/ui/, include/ui/):
 * - User interface and presentation logic
 * - X11 window management, dialogs, graphics
 * 
 * Main Application (this file):
 * - Orchestrates all layers and manages game flow
 * - Contains legacy functions during transition
 * - Acts as the composition root for dependency injection
 */

/* ========================================================================
 * APPLICATION INITIALIZATION AND MAIN GAME LOOP
 * ======================================================================== */

int main(int argc, char* argv[]) {
    // Initialize random seed for game
    setrnd(&seed[0], savseed = time((time_t*)0));
    
    // Initialize X11 UI system and process command line arguments
    xinit(theargc = argc, theargv = argv);
    
    // Start main game loop
    play();
    
    // Clean application exit
    exitus(0);
    return 0;
}

void play() {
    if (!resumebock || !playbock) {
        bockspiele = bockinc = ramschspiele = 0;
    } else if (playbock != 2) {
        ramschspiele = 0;
    }
    phase = GEBEN;
    do {
        computer();
        computer();
        hndl_events();
    } while (!quit);
}

/* ========================================================================
 * FILE I/O AND ERROR HANDLING
 * ======================================================================== */

// Moved to application/file_manager.c
// - get_game()
// - read_opt_srpk()
// - read_opt()
// - save_opt()
// - read_list()
// - save_list()
// - update_list()
// - set_prot()

/* ========================================================================
 * GAME LOGIC AND CARD EVALUATION
 * ======================================================================== */

// Moved to domain/skat_core.c
// - gutesblatt() - Check if hand is good
// - mischen() - Shuffle and deal cards
// - lower(c1, c2, n) - Compare two cards
// - sort(sn) - Sort player's cards
// - calc_rw(s) - Calculate reiz value

/* ========================================================================
 * GAME PHASE HANDLERS
 * ======================================================================== */

// Moved to application/game_engine.c
// - do_geben() - Handle dealing phase
// - do_sagen() - Player says bid
// - do_passen() - Player passes
// - do_akzept() - Player accepts bid
// - do_msagen() - Machine says bid
// - do_mhoeren() - Machine listens
// - do_entsch() - Bidding decision
// - do_reizen() - Handle bidding phase

// Moved to domain/skat_core.c
// - drueck(f, n, p) - Discard cards to skat
// - truempfe() - Move trumps to player
// - tr_voll(sn, f) - Check if trumps full
// - sage_kontra(sn) - Check if kontra possible
// - sage_re(sn) - Check if re possible
// - testgrand(bb, b, vh) - Test grand hand viability
// - calc_inhand(sn) - Calculate cards in hand
// - testhand() - Test hand game

// Moved to application/ai_engine.c
// Moved to application/game_engine.c
// - nextgame() - Advance to next game
// - save_skat() - Save skat cards
// - check_bockevents() - Check bock events
// - do_grandhand() - Handle grand hand
// - do_handspiel() - Handle hand game
// - do_druecken() - Handle discard phase
// - do_handok() - Hand confirmed
// - do_ansagen() - Handle announcements

// Moved to domain/skat_core.c
// - karobube() - Karo bube logic
// - karobubespielen() - Play karo bube

// Moved to application/game_engine.c
// - do_angesagt() - After announcement
// - spielphase() - Playing phase setup
// - get_next() - Process next trick
// - setsum() - Set/clear sums
// - modsum() - Modify sums
// - fill_st() - Fill trick history
// - maxnimm() - Max delay for trick
// - next_stich() - Advance to next trick
// - finishgame() - Finish game
// - do_next() - Next action

// Moved to domain/skat_core.c
// - calc_poss(s) - Calculate possible plays
// - c_high(f, h) - Calculate highest card
// - calc_high(f, s) - Calculate highest cards
// - zweihoechste(ci) - Check if two highest

/* ========================================================================
 * COMPUTER AI AND STRATEGY FUNCTIONS
 * ======================================================================== */

// Moved to application/ai_engine.c
// - ignorieren() - Check if card can be ignored
// - genugdrin() - Check enough points in trick
// - gewinnstich(f) - Try to win trick
// - uebernehmen(p, h, n) - Take over trick
// - schmieren() - Smear points
// - einstechen() - Stick in with low card
// - niedrighoch(f) - Play low then high
// - ueberdoerfer() - Over-trump strategy
// - bubeausspielen() - Lead with jack
// - trumpfausspielen() - Lead with trump
// - hochausspielen() - Lead high
// - schenke() - Give away trick
// - zehnblank(ci) - Check if ten is blank
// - fabwerfen() - Discard suit
// - abwerfen() - Discard card
// - buttern() - Butter strategy
// - hatas() - Has ace
// - schnippeln(f) - Snap strategy
// - nichtspitze() - Not spitze
// - spitzefangen() - Catch spitze
// - restbeimir() - Check rest with me
// - m_bvsp() - Vorhand spieler strategy
// - m_bmsp() - Mittelhand spieler
// - m_bhsp() - Hinterhand spieler
// - m_bvns() - Vorhand non-spieler
// - m_bmns() - Mittelhand non-spieler
// - m_bhns() - Hinterhand non-spieler
// - m_bsp() - AI for spieler in bid game
// - m_bns() - AI for non-spieler
// - make_best(s) - Main AI decision function
// - adjfb(s, v) - Adjust suit tracking
// - calc_drueck() - Calculate discard for AI
// - do_spielen() - Main game playing loop
// - computer() - Main AI coordination

/* End of XSkat Main Application */
