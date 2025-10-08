/*
    XSkat Domain Layer - Core Game Logic
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef SKAT_GAME_H
#define SKAT_GAME_H

#include "skat.h"

// This header has been refactored to remove duplicate definitions
// that are now centralized in skat.h.

// Game state structure
typedef struct {
  int cards[32];
  int inhand[4][8];
  int phase;
  int geber;
  int hoerer;
  int sager;
  int spieler;
  int trumpf;
  int handsp;
  int stich;
  int ausspl;
  int stsum;
  int astsum;
  int gstsum;
  int spgew;
  int spwert;
  int schwz;
  int nullv;
  long seed[2];
} skat_game_state_t;

// Additional function declarations  
int minmax(int depth);
int null_dicht(int sn, int handsp, int *skat, int *ufb, int *mfb, int *hfb);

#endif /* SKAT_GAME_H */