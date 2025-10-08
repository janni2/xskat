/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef DOMAIN_SKAT_CORE_H
#define DOMAIN_SKAT_CORE_H

#include <stdio.h>

/*
 * Domain Layer - Core Skat Game Logic
 * 
 * Pure game logic and rules implementation
 */

// Game logic and card evaluation
extern int get_game(void);
extern int gutesblatt(void);
extern void mischen(void);
extern int testhand(void);
extern void calc_drueck(void);
extern int check_bockevents(void);

// Game phase management
extern void do_geben(void);
extern void do_reizen(void);
extern void do_handspiel(void);
extern void do_druecken(void);
extern void do_ansagen(void);
extern void do_spielen(void);
extern void spielphase(void);

// Game state management
extern void nextgame(void);
extern void do_next(void);
extern void next_stich(void);
extern void calc_result(void);
extern void get_next(void);
extern void finishgame(void);

// Player actions
extern void do_sagen(int s, int w);
extern void do_passen(int s);
extern void do_akzept(int s);
extern void do_entsch(void);
extern void do_handok(void);
extern void do_angesagt(void);

// Card mechanics
extern void truempfe(void);
extern void karobube(void);
extern int karobubespielen(void);

// Configuration management
extern void read_opt(void);
extern void save_opt(void);
extern void read_list(void);
extern void save_list(void);
extern void update_list(void);
extern void set_prot(void);

// Utility functions
extern int maxnimm(void);
extern void fill_st(void);

#endif /* DOMAIN_SKAT_CORE_H */