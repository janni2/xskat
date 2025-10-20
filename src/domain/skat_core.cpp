
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

/*
 * Domain Layer - Core Skat Game Logic
 *
 * This file contains the core card evaluation, comparison, and game logic
 * functions extracted from skat.c. These functions implement the fundamental
 * rules and mechanics of the Skat card game.
 *
 * Functions in this file:
 * - Card comparison and sorting (lower, sort)
 * - Card distribution and hand management (mischen, drueck, truempfe, calc_inhand)
 * - Card value calculation (gutesblatt, calc_rw, testgrand, tr_voll, sage_kontra, sage_re, testhand)
 * - Card play evaluation (higher, calc_poss, c_high, calc_high, zweihoechste)
 * - Game result calculation (calc_result)
 * - Special game mechanics (karobube, karobubespielen)
 */

#include "skat.h"

// Standard library includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Domain layer includes
#include "domain/skat_core.h"
#include "domain/skat_constants.h"
#include "domain/utils.h"
#include "domain/null.h"
#include "domain/ramsch.h"

// Application layer includes
#include "application/file_manager.h"

// UI layer includes (for functions that still have UI dependencies)
#include "ui/xio.h"
#include "domain/skat_enums.h"

/* ========================================================================
 * CARD EVALUATION AND HAND ASSESSMENT
 * ======================================================================== */

int gutesblatt() {
  int i, c, tr, bb, bs, as, ze;
  int t[NUM_SUITS];

  t[0] = t[1] = t[2] = t[3] = 0;
  bb = bs = as = ze = 0;
  for (i = 0; i < CARDS_IN_INITIAL_DEAL; i++) {
    c = cards[i < CARDS_PER_PLAYER ? i : SKAT_OFFSET + i];
    if ((c & CARD_RANK_MASK) == BUBE) {
      bb++;
      if (i > HAND_SIZE_MINUS_ONE) bs++;
    } else
      t[c >> CARD_SUIT_SHIFT]++;
  }
  tr = 0;
  for (i = 1; i < NUM_SUITS; i++) {
    if (t[i] >= t[tr]) tr = i;
  }
  for (i = 0; i < CARDS_IN_INITIAL_DEAL; i++) {
    c = cards[i < CARDS_PER_PLAYER ? i : SKAT_OFFSET + i];
    if ((c & CARD_RANK_MASK) != BUBE && c >> CARD_SUIT_SHIFT != tr) {
      switch (c & CARD_RANK_MASK) {
        case AS:
          as++;
          break;
        case ZEHN:
          ze++;
          break;
      }
    }
  }
  tr += bb;
  return (tr > MIN_TRUMPS_MODERATE || (tr == MIN_TRUMPS_MODERATE && as + ze > 1) ||
          (bb > MIN_JACKS_FOR_RISK && as > 1)) && bs;
}

/* ========================================================================
 * CARD DISTRIBUTION AND SHUFFLING
 * ======================================================================== */

void mischen() {
  int i, j;
  static int savecards[TOTAL_CARDS];

  if (wieder) {
    for (i = 0; i < TOTAL_CARDS; i++) cards[i] = savecards[i];
    if (wieder == 1) {
      if (vorhandwn) rotateby = (rotateby + NUM_PLAYERS) % NUM_PLAYERS - 1;
      for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[i], &cards[CARDS_PER_PLAYER + i]);
      for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[CARDS_PER_PLAYER + i], &cards[SKAT_OFFSET + i]);
    } else if (wieder == NUM_PLAYERS) {
      if (vorhandwn) rotateby = (rotateby + RIGHT_OFFSET) % NUM_PLAYERS - 1;
      for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[i], &cards[SKAT_OFFSET + i]);
      for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[SKAT_OFFSET + i], &cards[CARDS_PER_PLAYER + i]);
    }
    wieder = 0;
  } else if (!get_game()) {
    do {
      for (i = 0; i < TOTAL_CARDS; i++) cards[i] = i;
      for (i = 0; i < TOTAL_CARDS; i++) swap(&cards[i], &cards[rndval(&seed[0], MAX_CARD_INDEX)]);
      for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[geber * CARDS_PER_PLAYER + i], &cards[i]);
      for (i = 0; i < CARDS_PER_PLAYER; i++)
        swap(&cards[hoerer * CARDS_PER_PLAYER + i], &cards[geber == 1 ? i : CARDS_PER_PLAYER + i]);
      if (rotateby < 0) {
        for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[i], &cards[CARDS_PER_PLAYER + i]);
        for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[CARDS_PER_PLAYER + i], &cards[SKAT_OFFSET + i]);
      } else if (rotateby > 0) {
        for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[i], &cards[SKAT_OFFSET + i]);
        for (i = 0; i < CARDS_PER_PLAYER; i++) swap(&cards[SKAT_OFFSET + i], &cards[CARDS_PER_PLAYER + i]);
      }
      gamenr++;
    } while ((pkoption == 1 || pkoption == 4) && numsp == 1 && !gutesblatt());
    if (pkoption > 1) pkoption = 0;
  }
  for (i = 0; i < TOTAL_CARDS; i++) savecards[i] = cards[i];
  setrnd(&seed[1], seed[0]);
  for (i = 0; i < TOTAL_CARDS; i++) gespcd[i] = 0;
  for (i = 0; i < NUM_SUITS; i++) gespfb[i] = 0;
  butternok = 0;
  for (i = 0; i < NUM_PLAYERS; i++) {
    for (j = 0; j < 5; j++) hatnfb[i][j] = 0;
  }
  gstsum = 0;
  astsum = 0;
}

/* ========================================================================
 * CARD COMPARISON AND SORTING
 * ======================================================================== */

int lower(int c1, int c2, int n) {
  int f1, f2, w1, w2;

  if (c1 < 0) return 1;
  if (c2 < 0) return 0;
  f1 = c1 >> CARD_SUIT_SHIFT;
  f2 = c2 >> CARD_SUIT_SHIFT;
  w1 = c1 & CARD_RANK_MASK;
  w2 = c2 & CARD_RANK_MASK;
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

void sort(int sn) {
  int i, j, f = sn * 10;
  int hatfb[4], fbsum, firstf, sptz;

  sortw[0] = 0;
  sortw[1] = 1;
  sortw[2] = 2;
  sortw[3] = 3;
  if (alternate[sn]) {
    hatfb[0] = hatfb[1] = hatfb[2] = hatfb[3] = 0;
    for (i = f; i < f + 10; i++) {
      if (cards[i] >= 0 && ((cards[i] & 7) != BUBE || sort2[sn])) {
        hatfb[cards[i] >> 3] = 1;
      }
    }
    if (!sort2[sn] && trumpf >= 0 && trumpf < 4 && hatfb[trumpf]) {
      hatfb[trumpf] = 0;
      firstf        = trumpf;
    } else
      firstf = -1;
    fbsum = hatfb[0] + hatfb[1] + hatfb[2] + hatfb[3];
    if ((hatfb[0] || hatfb[1]) && (hatfb[2] || hatfb[3])) {
      switch (fbsum) {
        case 4:
          sortw[1] = 2;
          sortw[2] = 1;
          break;
        case 3:
          if (hatfb[0] && hatfb[1]) {
            sortw[0] = 0;
            sortw[1] = 2;
            sortw[2] = sortw[3] = 1;
          } else {
            sortw[2] = 0;
            sortw[3] = 2;
            sortw[0] = sortw[1] = 1;
          }
          break;
        case 2:
          if (firstf > 1) {
            sortw[0] = sortw[1] = 1;
            sortw[2] = sortw[3] = 0;
          }
          break;
      }
    }
  }
  if (sn == spieler && spitzeang && !sort2[sn]) {
    sptz = trumpf == 4 ? BUBE : SIEBEN | trumpf << 3;
  } else
    sptz = -2;
  for (i = f; i < f + 9; i++) {
    for (j = i + 1; j < f + 10; j++) {
      if (((cards[j] == sptz || lower(cards[i], cards[j], sort2[sn])) &&
           cards[i] != sptz) ^
          sort1[sn]) {
        swap(&cards[i], &cards[j]);
      }
    }
  }
  sortw[0] = 0;
  sortw[1] = 1;
  sortw[2] = 2;
  sortw[3] = 3;
}

/* ========================================================================
 * REIZ VALUE CALCULATION
 * ======================================================================== */

void calc_rw(int s) {
  int i, c, f, tr, bb, as, ze, dk, stg;
  int b[4], t[4];

  maxrw[s] = 0;
  b[0] = b[1] = b[2] = b[3] = 0;
  t[0] = t[1] = t[2] = t[3] = 0;
  bb = as = ze = dk = 0;
  for (i = 0; i < 10; i++) {
    c = cards[10 * s + i];
    if ((c & 7) == BUBE) {
      b[c >> 3] = 1;
      bb++;
    } else
      t[c >> 3]++;
  }
  tr = 0;
  for (i = 1; i < 4; i++) {
    if (t[i] >= t[tr]) tr = i;
  }
  for (i = 0; i < 10; i++) {
    c = cards[10 * s + i];
    if ((c & 7) != BUBE && c >> 3 != tr) {
      switch (c & 7) {
        case AS:
          as++;
          break;
        case ZEHN:
          ze++;
          break;
        default:
          dk += cardw[c & 7];
      }
    }
  }
  if ((bb + t[tr] == 4 && ((as == 2 && ze >= 2) || (as >= 3))) ||
      (bb + t[tr] == 5 && ((dk + 10 * ze >= 39) ||
                           (as >= 1 && ze >= 1 && dk + 10 * ze >= 11 && b[3]) ||
                           (as >= 2 && dk + 10 * ze) || (as >= 3))) ||
      (bb + t[tr] == 6 && ((dk + 10 * ze >= 14) || (ze + as))) ||
      bb + t[tr] >= 7) {
    f = 2;
    if (b[3]) {
      while (f < 5 && b[4 - f]) f++;
    }
    maxrw[s] = f * rwert[tr];
  }
  if (!maxrw[s]) testnull(s);
  if (!maxrw[s] &&
      (((b[3] || b[2] || bb == 2) &&
        ((b[3] && b[2] && as >= 2) ||
         (bb + t[tr] == 4 && as >= 1 && dk + 10 * ze + 11 * as >= 29) ||
         (bb + t[tr] == 5 && dk + 10 * ze + 11 * as >= 19) ||
         (bb + t[tr] == 5 && ze + as > 1) || (bb + t[tr] == 6 && bb > 2) ||
         (bb + t[tr] == 6 && dk + 10 * ze >= 8))) ||
       (bb + t[tr] == 4 && bb && as > 1) || (bb + t[tr] == 5 && as > 1) ||
       (bb + t[tr] == 5 && dk + 10 * ze + 11 * as >= 32)))
    maxrw[s] = 18;
  if (!maxrw[s] &&
      (((b[3] || b[2] || bb == 2) && (bb + t[tr] == 6)) ||
       (bb + t[tr] == 4 && bb > 1 && as) ||
       (bb + t[tr] == 4 && bb && as && ze && dk) ||
       (bb + t[tr] == 5 && bb && as && ze) ||
       (bb + t[tr] == 5 && bb && ze && dk > 4) ||
       (bb + t[tr] == 5 && bb && ze > 1) || (bb + t[tr] == 5 && bb > 1) ||
       (bb + t[tr] == 6 && dk + 10 * ze + 11 * as >= 8)))
    maxrw[s] = 17;
  stg = strateg[numsp == 0 ? s : numsp == 1 ? s - 1 : 0];
  if (stg < 0 && rnd(3) < -stg) {
    if (maxrw[s] > 17)
      maxrw[s] = 17;
    else if (maxrw[s] == 17 || rnd(7) < -stg)
      maxrw[s] = 2 * rwert[tr];
    else
      maxrw[s] = 17;
  }
}

/* ========================================================================
 * CARD HAND MANAGEMENT
 * ======================================================================== */

void drueck(int f, int n, int *p) {
  int i, j;

  for (i = trumpf != 5; i < 8 && n && gedr < 2; i++) {
    if (inhand[f][i]) {
      inhand[f][i] = 0;
      (*p) -= cardw[i];
      if (!gedr && cards[31] == (f << 3) + i) {
        swap(&cards[30], &cards[31]);
      } else {
        for (j = 0; j < 10; j++) {
          if (cards[spieler * 10 + j] == (f << 3) + i) {
            swap(&cards[30 + gedr], &cards[10 * spieler + j]);
            break;
          }
        }
      }
      gedr++;
      n--;
    }
  }
}

void truempfe() {
  int i, c;

  for (c = 0; c < 2; c++) {
    if ((cards[30 + c] & 7) == BUBE || cards[30 + c] >> 3 == trumpf) {
      for (i = 0; i < 10; i++) {
        if ((cards[10 * spieler + i] & 7) != BUBE &&
            cards[10 * spieler + i] >> 3 != trumpf) {
          swap(&cards[30 + c], &cards[10 * spieler + i]);
          break;
        }
      }
    }
  }
}

int tr_voll(int sn, int f) {
  int i, c, t, a, z, n[4], ze[4];

  if (trumpf == -1 || trumpf == 4) return f;
  t = a = z = 0;
  n[0] = n[1] = n[2] = n[3] = 0;
  ze[0] = ze[1] = ze[2] = ze[3] = 0;
  for (i = 0; i < 10; i++) {
    c = cards[10 * sn + i];
    if ((c & 7) == BUBE || c >> 3 == trumpf)
      t++;
    else if ((c & 7) == AS)
      a++;
    else if ((c & 7) == ZEHN)
      z++, ze[c >> 3] = 1;
    else
      n[c >> 3]++;
  }
  if (f) {
    return t > 7 || (t > 6 && a + z);
  }
  return (t > 5 || (t > 4 && a + z) || (t > 3 && a > 2)) &&
         !(t == 4 && ((ze[0] && !n[0]) || (ze[1] && !n[1]) ||
                      (ze[2] && !n[2]) || (ze[3] && !n[3])));
}

int sage_kontra(int sn) { return tr_voll(sn, 0); }

int sage_re(int sn) { return tr_voll(sn, 1); }

int testgrand(int bb, int b[4], int vh) {
  int i, j, fl, ih, g3, g4, as, ze, ko, a[4], bz;

  bz = 2;
  for (j = 0; j < 4; j++) {
    a[j] = 0;
    for (i = 0; i < 8; i++) {
      if (i >= BUBE || i == ZEHN) continue;
      a[j] += inhand[j][i];
    }
    if (inhand[j][ZEHN] && !a[j]) bz = 1;
  }
  if (bb == 2 && spieler != ausspl) bz = 1;
  as = inhand[0][AS] + inhand[1][AS] + inhand[2][AS] + inhand[3][AS];
  ze = inhand[0][ZEHN] + inhand[1][ZEHN] + inhand[2][ZEHN] + inhand[3][ZEHN];
  ko = inhand[0][KOENIG] + inhand[1][KOENIG] + inhand[2][KOENIG] +
       inhand[3][KOENIG];
  if (bb == 2 && as > 2 && ze) return bz;
  if (bb && as > 2 && ze == 4) return bz;
  if (as == 4 && ze > 3 - bb) return 2;
  if (as == 4 && ze > 2 - bb) return 1;
  if (bb <= 2 && (!b[3] || bb != 2 || spieler != ausspl)) return 0;
  fl = g3 = g4 = 0;
  for (i = 0; i < 4; i++) {
    ih = 0;
    for (j = 0; j < 8; j++) {
      if (j != BUBE && inhand[i][j]) ih++;
    }
    for (j = 0; j < 8; j++) {
      if (j != BUBE) {
        if (inhand[i][j])
          fl++;
        else if (7 - ih > j)
          break;
      }
    }
    if ((ih > 4) || (ih > 3 && (inhand[i][AS] || inhand[i][ZEHN]))) g4 = 1;
    if (ih > 4 && (inhand[i][AS] || inhand[i][ZEHN])) g3 = 1;
    if (ih > 3 && inhand[i][AS] && inhand[i][ZEHN]) g3 = 1;
  }
  if (fl + bb > 5) return bz;
  if (bb == 4 && g4) return bz;
  if ((bb == 3 && (b[3] || vh) && g3)) return bz;
  return fl + bb > 4 && b[3] && !(bb + as == 5 && !ze && !ko);
}

void calc_inhand(int sn) {
  int i, c;

  for (i = 0; i < 4; i++) {
    for (c = 0; c < 8; c++) inhand[i][c] = 0;
  }
  for (i = 0; i < 10; i++) {
    c = cards[10 * sn + i];
    if (c >= 0) {
      inhand[c >> 3][c & 7] = 1;
    }
  }
}

int testhand() {
  int i, c, f, bb, as;
  int b[4], t[4], p[4], o[4];

  for (i = 0; i < 4; i++) {
    b[i] = t[i] = p[i] = 0;
    o[i]               = i;
  }
  bb = 0;
  for (i = 0; i < 4; i++) {
    for (c = 0; c < 8; c++) inhand[i][c] = 0;
  }
  for (i = 0; i < 10; i++) {
    c = spcards[i];
    if ((c & 7) == BUBE) {
      b[c >> 3] = 1;
      bb++;
    } else {
      p[c >> 3] += cardw[c & 7];
      t[c >> 3]++;
      inhand[c >> 3][c & 7] = 1;
    }
  }
  for (i = 1; i < 4; i++) {
    if (inhand[i][ZEHN] && !inhand[i][AS] && !inhand[i][KOENIG]) {
      o[i] = 0;
      o[0] = i;
      break;
    }
  }
  f = 3;
  while (f < 5 && b[4 - f] == b[3]) f++;
  trumpf = 0;
  while (f * rwert[trumpf] < reizw[reizp]) trumpf++;
  for (i = trumpf + 1; i < 4; i++) {
    if (t[i] > t[trumpf] || (t[i] == t[trumpf] && p[i] <= p[trumpf]))
      trumpf = i;
  }
  if (testgrand(bb, b, spieler == ausspl) == 2) {
    trumpf = 4;
    return 1;
  }
  as = 0;
  for (i = 0; i < 4; i++) {
    if (inhand[i][AS] && i != trumpf) as++;
  }
  if (t[trumpf] + bb > 7 && as) return 1;
  return 0;
}

/* ========================================================================
 * SPECIAL GAME MECHANICS
 * ======================================================================== */

void karobube() {
  int s, i, n, k, c;

  karobubeanz = 0;
  if (trumpf < 0 || trumpf > 3) return;
  for (s = 0; s < 3; s++) {
    if (s == spieler) continue;
    n = k = 0;
    for (i = 0; i < 10; i++) {
      c = cards[s * 10 + i];
      if ((c & 7) == BUBE || c >> 3 == trumpf) {
        n++;
        if ((c & 7) < KOENIG) n = 9;
        if (c == BUBE)
          k = 1;
        else if ((c & 7) == BUBE)
          n = 9;
      }
    }
    if (k && n == 2) {
      karobubeanz = 1;
    }
  }
}

int karobubespielen() {
  int i;

  if (!karobubeanz) return 0;
  for (i = 0; i < possc; i++) {
    if (cards[possi[i]] == BUBE) {
      playcd = i;
      return 1;
    }
  }
  return 0;
}

/* ========================================================================
 * CARD PLAY COMPARISON
 * ======================================================================== */

int higher(int c1, int c2) {
  int f1, w1, f2, w2;

  if (c2 == -1) return 1;
  f1 = c1 >> 3;
  w1 = c1 & 7;
  f2 = c2 >> 3;
  w2 = c2 & 7;
  if (trumpf == -1) {
    if (f1 == f2) {
      if (w1 == ZEHN) return w2 > BUBE;
      if (w2 == ZEHN) return w1 <= BUBE;
      return w1 < w2;
    }
    return 1;
  }
  if (w1 == BUBE) {
    if (w2 == BUBE)
      return f1 > f2;
    else
      return 1;
  }
  if (w2 == BUBE) return 0;
  if (f1 == f2) return w1 < w2;
  if (f2 == trumpf) return 0;
  return 1;
}

/* ========================================================================
 * GAME RESULT CALCULATION
 * ======================================================================== */

void calc_result() {
  int i, c, f;
  int b[4], s[8];

  mes1 = mes2 = mes3 = mes4 = 0;
  if (trumpf == 5) {
    ramsch_result();
    return;
  }
  if (trumpf == -1) {
    spwert = nullw[revolang ? 4 : (ouveang ? 2 : 0) + handsp];
    if (nullv) {
      spgew = 0;
      if (!handsp || !oldrules) spwert *= 2;
      nspwert = 0;
    } else {
      spgew   = 1;
      nspwert = spwert;
    }
    for (i = 0; i < kontrastufe; i++) spwert *= 2;
    if (bockspiele) spwert *= 2;
    return;
  }
  if (stich == 1 && schenkstufe) {
    stsum = 61;
    schwz = 0;
    nullv = 1;
  }
  b[0] = b[1] = b[2] = b[3] = 0;
  s[0] = s[1] = s[2] = s[3] = s[4] = s[5] = s[6] = s[7] = 0;
  for (i = 0; i < 12; i++) {
    c = spcards[i];
    if ((c & 7) == BUBE)
      b[c >> 3] = 1;
    else if (c >> 3 == trumpf)
      s[c & 7] = 1;
  }
  s[BUBE] = s[NEUN];
  s[NEUN] = s[ACHT];
  s[ACHT] = s[SIEBEN];
  f       = 1;
  while (f < 4 && b[3 - f] == b[3]) f++;
  if (f == 4 && trumpf != 4) {
    while (f < 11 && s[f - 4] == b[3]) f++;
  }
  f++;
  if (handsp) f++;
  if (stsum >= 90 || schnang || stsum <= 30) f++;
  if (schnang) f++;
  if (schwz || schwang || !nullv) f++;
  if (schwang) f++;
  if (ouveang) f++;
  if (spitzeang) f += spitzezaehlt;
  if (trumpf == 4 && ouveang && oldrules)
    spwert = (f - 1) * 36;
  else
    spwert = f * rwert[trumpf];
  if ((stsum > 60 && spwert >= reizw[reizp] && (stsum >= 90 || !schnang) &&
       (schwz || !schwang) && (spitzeok || !spitzeang)) ||
      stich == 1) {
    spgew   = 1;
    nspwert = spwert;
  } else {
    if (spwert < reizw[reizp])
      mes1 = 1;
    else if (schnang && stsum < 90)
      mes2 = 1;
    else if (schwang && !schwz)
      mes3 = 1;
    else if (spitzeang && !spitzeok)
      mes4 = 1;
    spgew = 0;
    if (spwert < reizw[reizp]) {
      spwert = ((reizw[reizp] - 1) / rwert[trumpf] + 1) * rwert[trumpf];
    }
    if (!handsp || !oldrules) spwert *= 2;
    nspwert = 0;
  }
  for (i = 0; i < kontrastufe; i++) spwert *= 2;
  if (bockspiele && !ramschspiele) spwert *= 2;
}

/* ========================================================================
 * POSSIBLE CARD PLAYS CALCULATION
 * ======================================================================== */

void calc_poss(int s) {
  int i, j, k, f1, w1, f2, w2;

  possc = 0;
  for (i = 0; i < 10; i++) {
    if (cards[s * 10 + i] >= 0) {
      for (j = 0; j < possc && cards[s * 10 + i] > cards[possi[j]]; j++);
      for (k = possc; k > j; k--) possi[k] = possi[k - 1];
      possi[j] = s * 10 + i;
      possc++;
    }
  }
  if (vmh) {
    f1 = stcd[0] >> 3;
    w1 = stcd[0] & 7;
    if (trumpf != -1 && w1 == BUBE) f1 = trumpf;
    i = j = 0;
    do {
      f2 = cards[possi[i]] >> 3;
      w2 = cards[possi[i]] & 7;
      if (trumpf != -1 && w2 == BUBE) f2 = trumpf;
      if (f1 == f2) possi[j++] = possi[i];
    } while (++i < possc);
    if (j)
      possc = j;
    else
      hatnfb[s][f1 > 4 ? 4 : f1] = 1;
  }
}

void c_high(int f, int* h) {
  int i, j;

  h[0] = h[1] = h[2] = h[3] = h[4] = -1;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 8; j++) {
      if (j == BUBE) j++;
      if (gespcd[i << 3 | j] < f) {
        h[i] = i << 3 | j;
        break;
      }
    }
  }
  for (i = 3; i >= 0; i--) {
    if (gespcd[i << 3 | BUBE] < f) {
      h[trumpf] = i << 3 | BUBE;
      break;
    }
  }
}

void calc_high(int f, int s) {
  int i, gespsav[32];

  c_high(f, high);
  if (!s) return;
  for (i = 0; i < 32; i++) gespsav[i] = gespcd[i];
  for (i = 0; i < 5; i++) {
    if (high[i] >= 0) gespcd[high[i]] = 2;
  }
  c_high(f, shigh);
  for (i = 0; i < 32; i++) gespcd[i] = gespsav[i];
}

int zweihoechste(int ci) {
  int i, tr, trdr;
  int cj = ci;
  Suit trump_suit = (Suit)trumpf;

  calc_high(1, 1);

  if (ci != high[trumpf]) {
    return 0;
  }

  for (i = 0; i < possc; i++) {
    cj = cards[possi[i]];
    if (cj == shigh[trumpf]) {
      break;
    }
  }

  tr = 0;
  for (i = 0; i < possc; i++) {
    int current_card = cards[possi[i]];
    Suit card_suit = (Suit)(current_card >> 3);
    Rank card_rank = (Rank)(current_card & 7);

    if (card_rank == RANK_BUBE || (trump_suit < 4 && card_suit == trump_suit)) {
      tr++;
    }
  }

  if (trump_suit < 4) {
    trdr = 7 - gespfb[trump_suit];
  } else {
    trdr = 0;
  }

  for (int s = SUIT_KREUZ; s <= SUIT_KARO; s++) {
    if (!gespcd[s << 3 | RANK_BUBE]) {
      trdr++;
    }
  }

  return ci != cj && cj == shigh[trumpf] && trdr - tr <= 1;
}
