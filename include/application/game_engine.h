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

#ifndef APPLICATION_GAME_ENGINE_H
#define APPLICATION_GAME_ENGINE_H

/*
 * Application Layer - Game Engine
 * 
 * Core game coordination and flow management
 */

// Main game loop and coordination
extern void play(void);
extern void computer(void);

// Game initialization and lifecycle
extern void game_init(void);
extern void nextgame(void);
extern void finishgame(void);

// Game flow control functions
extern void do_geben(void);
extern void do_reizen(void);
extern void do_handspiel(void);
extern void do_druecken(void);
extern void do_ansagen(void);
extern void do_spielen(void);
extern void spielphase(void);

// Game state management
extern void do_next(void);
extern void next_stich(void);
extern void calc_result(void);
extern void get_next(void);

// Game logic helpers
extern int get_game(void);
extern int gutesblatt(void);
extern void mischen(void);
extern int testhand(void);
extern void calc_drueck(void);
extern int check_bockevents(void);

// Player action handlers
extern void do_sagen(int s, int w);
extern void do_passen(int s);
extern void do_akzept(int s);
extern void do_entsch(void);
extern void do_handok(void);
extern void do_angesagt(void);

// Card game mechanics
extern void truempfe(void);
extern void karobube(void);
extern int karobubespielen(void);

// AI and computer player logic
extern int ignorieren(void);
extern int genugdrin(void);
extern void schmieren(void);
extern int einstechen(void);
extern int ueberdoerfer(void);
extern int bubeausspielen(void);
extern int trumpfausspielen(void);
extern int hochausspielen(void);
extern void schenke(void);
extern int fabwerfen(void);
extern void abwerfen(void);
extern int buttern(void);
extern int hatas(void);
extern void nichtspitze(void);
extern int spitzefangen(void);
extern int restbeimir(void);

// Move calculation functions
extern void m_bvsp(void);
extern void m_bmsp(void);
extern void m_bhsp(void);
extern void m_bvns(void);
extern void m_bmns(void);
extern void m_bhns(void);
extern void m_bsp(void);
extern void m_bns(void);

// Utility functions
extern int maxnimm(void);
extern void fill_st(void);

#endif /* APPLICATION_GAME_ENGINE_H */