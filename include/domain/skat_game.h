/*
    XSkat Domain Layer - Core Game Logic
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef SKAT_GAME_H
#define SKAT_GAME_H

// Card definitions
#define AS 0
#define ZEHN 1
#define KOENIG 2
#define DAME 3
#define BUBE 4
#define NEUN 5
#define ACHT 6
#define SIEBEN 7

// Game phases
enum game_phase {
  GEBEN,
  REIZEN,
  HANDSPIEL,
  DRUECKEN,
  ANSAGEN,
  REVOLUTION,
  SPIELEN,
  SCHENKEN,
  NIMMSTICH,
  SPIELDICHT,
  WEITER,
  RESULT
};

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

// Temporary global state access (will be refactored)
extern int cards[32], gespcd[32];
extern int inhand[4][8];
extern int numsp, geber, hoerer, sager, spieler;
extern int trumpf, handsp, stich, ausspl;
extern int stsum, astsum, gstsum, spgew, spwert;
extern int schwz, nullv, butternok;
extern long seed[2], gamenr;
extern int wieder, vorhandwn, rotateby, pkoption;
extern int sortw[4], gespfb[4], hatnfb[3][5];
extern int possi[10], possc, stcd[3];
extern int nullw[5], reizw[72], cardw[8];
extern int revolution, revolang, vmh, playcd;
extern int maxrw[3];

// Additional types and structs needed by domain layer
typedef struct {
    int skat[2][2];
} prot_t;
extern prot_t prot2;

// Additional function declarations  
int minmax(int depth);
int higher(int c1, int c2);
int null_dicht(int sn, int handsp, int *skat, int *ufb, int *mfb, int *hfb);

// Core game functions
int left(int s);
int right(int s);
int iscomp(int s);
void setrnd(long *s, long v);
int rndval(long *s, int m);
int rnd(int m);
void mischen(void);
int lower(int c1, int c2, int n);
void calc_rw(int s);
void do_geben(void);
void do_reizen(void);
int testhand(void);
void truempfe(void);
int tr_voll(int sn, int f);

// Card handling functions
void swap(int *i, int *j);
void sort(int sn);
void calc_inhand(int sn);

// Game logic validation
int gutesblatt(void);

#endif /* SKAT_GAME_H */