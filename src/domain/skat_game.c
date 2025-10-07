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

// Basic utility functions
int left(int s) {
    return (s + 1) % 3;
}

int right(int s) {
    return (s + 2) % 3;
}

int iscomp(int s) {
    return s >= numsp;
}

void swap(int *i, int *j) {
    int h = *i;
    *i = *j;
    *j = h;
}

void setrnd(long *s, long v) {
    *s = v << 1 ? v : -1;
}

int rndval(long *s, int m) {
    register long h = *s;
    int i;
    
    for (i = 0; i < 7; i++)
        h = (h << 16) | ((((h << 1) ^ (h << 4)) >> 16) & 0xffff);
    *s = h;
    return h & m;
}

int rnd(int m) {
    return rndval(&seed[1], m);
}

// Card comparison function
int lower(int c1, int c2, int n) {
    int f1, f2, w1, w2;
    
    if (c1 < 0) return 1;
    if (c2 < 0) return 0;
    f1 = c1 >> 3;
    f2 = c2 >> 3;
    w1 = c1 & 7;
    w2 = c2 & 7;
    
    if (n) {
        if (sortw[f1] < sortw[f2]) return 1;
        if (sortw[f1] > sortw[f2]) return 0;
        if (w1 == ZEHN) return w2 <= BUBE;
        if (w2 == ZEHN) return w1 > BUBE;
        return w1 > w2;
    }
    
    if (w2 == BUBE) {
        if (w1 != BUBE) return 1;
        return f1 < f2;
    } else {
        if (w1 == BUBE) return 0;
        if (f2 == trumpf && f1 != trumpf) return 1;
        if (f1 == trumpf && f2 != trumpf) return 0;
        if (sortw[f1] < sortw[f2]) return 1;
        if (sortw[f1] > sortw[f2]) return 0;
        return w1 > w2;
    }
}

// Card sorting function
void sort(int sn) {
    int i, j, f = sn * 10;
    int hatfb[4], fbsum, firstf, sptz;
    
    sortw[0] = 0;
    sortw[1] = 1;
    sortw[2] = 2;
    sortw[3] = 3;
    
    for (i = 0; i < 4; i++) hatfb[i] = 0;
    for (i = 0; i < 10; i++) {
        if (cards[f + i] >= 0) hatfb[cards[f + i] >> 3] = 1;
    }
    
    fbsum = hatfb[0] + hatfb[1] + hatfb[2] + hatfb[3];
    if (fbsum == 4 || fbsum == 1) {
        firstf = hatfb[1] ? 1 : hatfb[2] ? 2 : hatfb[3] ? 3 : 0;
        sortw[firstf] = 0;
        sortw[(firstf + 1) & 3] = 1;
        sortw[(firstf + 2) & 3] = 2;
        sortw[(firstf + 3) & 3] = 3;
    }
    
    for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 10; j++) {
            if (lower(cards[f + i], cards[f + j], 1)) {
                swap(&cards[f + i], &cards[f + j]);
            }
        }
    }
}

// Check if hand is good enough for automated play
int gutesblatt(void) {
    int i, j, c, f, w, bb[4], buben = 0;
    
    for (i = 0; i < 4; i++) bb[i] = 0;
    for (i = 0; i < 10; i++) {
        c = cards[i];
        f = c >> 3;
        w = c & 7;
        bb[f]++;
        if (w == BUBE) buben++;
    }
    
    // Simple heuristic: good if has buben or long suit
    if (buben >= 2) return 1;
    for (i = 0; i < 4; i++) {
        if (bb[i] >= 4) return 1;
    }
    return 0;
}

// Calculate hand contents
void calc_inhand(int sn) {
    int i, j, f = sn * 10;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            inhand[i][j] = 0;
        }
    }
    
    for (i = 0; i < 10; i++) {
        if (cards[f + i] >= 0) {
            int card = cards[f + i];
            int suit = card >> 3;
            int rank = card & 7;
            inhand[suit][rank] = 1;
        }
    }
}

// Trump analysis
void truempfe(void) {
    int i, s, c, f, w;
    
    for (s = 0; s < 3; s++) {
        hatnfb[s][trumpf] = 0;
        for (i = 0; i < 10; i++) {
            c = cards[s * 10 + i];
            if (c >= 0) {
                f = c >> 3;
                w = c & 7;
                if (w == BUBE || f == trumpf) {
                    hatnfb[s][trumpf]++;
                }
            }
        }
    }
}

// Check if player has full trump suit
int tr_voll(int sn, int f) {
    int i, c, w, count = 0;
    
    for (i = 0; i < 10; i++) {
        c = cards[sn * 10 + i];
        if (c >= 0) {
            w = c & 7;
            if (w == BUBE || (c >> 3) == f) {
                count++;
            }
        }
    }
    
    return count >= 5; // Arbitrary threshold for "full"
}

// Test if hand game is viable
int testhand(void) {
    int i, c, buben = 0, trumps = 0;
    
    for (i = 0; i < 10; i++) {
        c = cards[spieler * 10 + i];
        if (c >= 0) {
            int w = c & 7;
            int f = c >> 3;
            if (w == BUBE) buben++;
            if (f == trumpf) trumps++;
        }
    }
    
    return (buben + trumps) >= 5; // Simple hand game test
}