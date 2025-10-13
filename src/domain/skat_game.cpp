/*
    XSkat Domain Layer - Core Game Logic Implementation
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#include "domain/skat_game.h"
#include <stdio.h>
#include <stdlib.h>

// External references to global state (will be refactored)
extern int cards[32], gespcd[32];
extern int inhand[4][8];
extern int numsp, geber, hoerer, sager, spieler;
extern int trumpf, handsp, stich, ausspl;
extern int stsum, astsum, gstsum, spgew, spwert;
extern int schwz, nullv, butternok;
extern long seed[2], gamenr;
extern int wieder, vorhandwn, rotateby, pkoption;
extern int sortw[4], gespfb[4], hatnfb[3][5];

// This file is intentionally left empty after refactoring.
// The functions previously in this file were duplicates of functions
// in skat_core.c and utils.c. To resolve "multiple definition"
// linker errors, the content of this file was removed. It is now
// compiled as an empty translation unit.