/*
    XSkat Domain Layer - Null Game Logic
    Copyright (C) 2000  Gunter Gerhardt

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

#include "domain/null.h"
#include "domain/skat_game.h"

// Domain-specific null game state
int wirftabfb[4] = {0};
int hattefb[4]   = {0};
int aussplfb[4]  = {0};
int nochinfb[4]  = {0};
int naussplfb[3] = {0};

void init_null() {
  int i;

  for (i = 0; i < 4; i++) {
    wirftabfb[i] = 0;
    hattefb[i]   = 0;
    aussplfb[i]  = 0;
    nochinfb[i]  = 8;
  }
  for (i = 0; i < 3; i++) {
    naussplfb[i] = -1;
  }
}

void testnull(int sn) {
  int i, f, c;
  int a[4], l[4], n[4], m[4], h[4], s[4], mfb[4];

  naussplfb[sn] = -1;
  if (null_dicht(sn, 1, &cards[30], (int*)0, mfb, (int*)0)) {
    for (i = 0; i < 4 && mfb[i]; i++);
    if (sn != ausspl || i < 4) {
      f = aussplfb[i < 4 ? i : 0];
      maxrw[sn] = nullw[revolution ? 4 : 3];
      naussplfb[sn] = f;
    }
  }
}

int kleiner_w(int w1, int w2) {
  return (w1 == AS && w2 != AS) || (w1 > w2 && w2 != AS);
}

int kleiner(int i, int j) {
  return kleiner_w(cards[possi[i]] & 7, cards[possi[j]] & 7);
}

int hat(int i) {
  return !hatnfb[spieler][cards[possi[i]] >> 3];
}

int n_anwert(int fb) {
  int i, b = 0, m;

  if (hatnfb[spieler][fb]) return 0;
  for (i = 7; i >= 0; i--) {
    if (gespcd[fb << 3 | i] != 2) break;
  }
  if (stich > 1) {
    m = left(ausspl) != spieler ? left(ausspl) : right(ausspl);
    if (!hatnfb[m][fb]) b = 64;
  }
  return b + (i >= 0 ? (i << 3) + fb + 1 : 0);
}

int n_anspiel() {
  int i, ci, cf, cw, bw = 0, pos = 0;

  for (i = 1; i < possc; i++) {
    ci = cards[possi[i]];
    cf = ci >> 3;
    cw = ci & 7;
    if (cw > bw) {
      bw = cw;
      pos = i;
    }
  }
  return pos;
}

int n_abwert(int min_fb) {
  int i, ci, cf, cw, bw = 0, pos = 0;

  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    cf = ci >> 3;
    cw = ci & 7;
    if (cf >= min_fb && cw > bw) {
      bw = cw;
      pos = i;
    }
  }
  return pos;
}

int n_bedienen() {
  int i, anz = 0, ci, cf, pos = 0;
  int f = stcd[0] >> 3;

  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    cf = ci >> 3;
    if (cf == f) {
      anz++;
      if (kleiner(i, pos)) pos = i;
    }
  }
  return anz ? pos : -1;
}

int n_nicht_bed() {
  int i, ci, cf, cw, bw = 0, pos = 0;

  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    cf = ci >> 3;
    cw = ci & 7;
    if (cw > bw) {
      bw = cw;
      pos = i;
    }
  }
  return pos;
}

int n_abwerfen() {
  int i, j, ci, cj, wi, wj;

  j = 0;
  for (i = 1; i < possc; i++) {
    ci = cards[possi[i]];
    cj = cards[possi[j]];
    wi = n_anwert(ci);
    wj = n_anwert(cj);
    if (wi > wj || (wi == wj && !kleiner(i, j))) j = i;
  }
  return j;
}

int minmax(int f) {
  int i, j, hi, hj;

  j = 0;
  for (i = 1; i < possc; i++) {
    hi = hat(i);
    hj = hat(j);
    if ((hi && !hj) || (kleiner(i, j) ^ f && (hi || !hj))) j = i;
  }
  return j;
}

int minmaxfb(int f, int fb) {
  int i, j = -1;

  for (i = 0; i < possc; i++) {
    if ((j < 0 && cards[possi[i]] >> 3 == fb) ||
        (cards[possi[i]] >> 3 == fb && kleiner(i, j) ^ f))
      j = i;
  }
  return j < 0 ? 0 : j;
}

int drunter(int f) {
  int i, j;

  j = 0;
  for (i = 1; i < possc; i++) {
    if (higher(cards[possi[j]], cards[possi[i]])) j = i;
  }
  for (i = 0; i < possc; i++) {
    if (higher(stcd[f], cards[possi[i]]) &&
        higher(cards[possi[i]], cards[possi[j]]))
      j = i;
  }
  return j;
}

int drunterdrue() {
  int i, w, fb;

  fb = stcd[0] >> 3;
  i  = -1;
  for (w = stcd[0] & 7; w >= AS; w = w == NEUN     ? ZEHN
                                     : w == ZEHN   ? BUBE
                                     : w == KOENIG ? AS
                                                   : w - 1) {
    if (i < 0) {
      i = 0;
      continue;
    }
    for (i = 0; i < possc; i++) {
      if (cards[possi[i]] == (fb << 3 | w)) return i;
    }
    if (gespcd[fb << 3 | w] != 2) break;
  }
  return drunter(0);
}

void m_nsp() {
  int ufb;

  if (!vmh) {
    if (naussplfb[spieler] == -1) {
      playcd = minmax(0);
    } else {
      playcd = minmaxfb(0, naussplfb[spieler]);
    }
  } else if (hatnfb[spieler][stcd[0] >> 3]) {
    if (null_dicht(spieler, handsp, &prot2.skat[1][0], &ufb, (int*)0,
                   (int*)0)) {
      playcd = minmax(1);
    } else {
      playcd = minmaxfb(1, ufb);
    }
  } else
    playcd = drunter(vmh == 2 ? !higher(stcd[0], stcd[1]) : 0);
}

void m_nns(int s) {
  int sga = spieler == geber, ufb = stcd[0] >> 3;

  if (revolang && spieler != ausspl) {
    playcd = minmax(0);
    return;
  }

  if (!vmh)
    playcd = n_bedienen();
  else if (hatnfb[s][stcd[0] >> 3])
    playcd = n_anwert(ufb);
  else {
    playcd = n_bedienen();
    if (playcd < 0) {
      if (sga) {
        if (naussplfb[s] >= 0 && naussplfb[s] == ufb)
          playcd = n_nicht_bed();
        else
          playcd = n_anwert(ufb);
      } else {
        playcd = n_anwert(ufb);
      }
    } else {
      if (!higher(stcd[!sga], cards[possi[playcd]])) {
        playcd = n_nicht_bed();
      }
    }
  }
}

void null_stich() {
  int i;
  int fb1 = stcd[0] >> 3;

  for (i = 0; i < 3; i++) {
    nochinfb[stcd[i] >> 3]--;
  }

  if (ausspl != spieler) {
    aussplfb[fb1] = 1;
    hattefb[fb1] = 1;
  }
}

void null_sort(int *arr, int cnt) {
  int i, swp;

  do {
    swp = 0;
    for (i = 0; i < cnt - 1; i++) {
      if (kleiner_w(arr[i + 1], arr[i])) {
        swap(&arr[i], &arr[i + 1]);
        swp = 1;
      }
    }
  } while (swp);
}

void revolutiondist() {
  int i, j, k, p, c, sn, mi, fb, ufb, cnt;
  int cd[4][8], cdc[4], mfb[4], ct[3], sfb[4];

  sn = spieler == ausspl ? left(spieler) : ausspl;
  mi = left(sn) == spieler ? left(spieler) : left(sn);
  if (null_dicht(spieler, 0, (int*)0, &ufb, mfb, sfb)) {
    for (fb = 0; fb < 4 && mfb[fb] != 1; fb++);
    if (spieler != ausspl || fb == 4) return;
    ct[0] = ct[1] = ct[2] = 0;
    for (fb = 0; fb < 4; fb++) {
      if (mfb[sfb[fb]] == 1) {
        p = ct[sn] < ct[mi] ? sn : mi;
        for (j = 0, k = sn; j < 2 && ct[p] != 10; j++, k = mi) {
          for (i = 0; i < 10 && ct[p] != 10; i++) {
            c = cards[10 * k + i];
            if (c >> 3 == sfb[fb]) {
              swap(&cards[10 * k + i], &cards[10 * p + ct[p]]);
              ct[p]++;
            }
          }
        }
      }
    }
    return;
  }
  cdc[0] = cdc[1] = cdc[2] = cdc[3] = 0;
  cnt = 0;
  for (j = 0, k = sn; j < 2; j++, k = mi) {
    for (i = 0; i < 10; i++) {
      c = cards[10 * k + i];
      if (c >> 3 == ufb) {
        swap(&cards[10 * k + i], &cards[10 * sn + cnt]);
        cnt++;
      }
    }
  }
  for (j = 0, k = sn; j < 2; j++, k = mi) {
    for (i = 0; i < 10; i++) {
      c = cards[10 * k + i];
      cd[c >> 3][cdc[c >> 3]++] = c & 7;
    }
  }
  for (fb = 0; fb < 4; fb++) {
    null_sort(cd[fb], cdc[fb]);
  }
  fb = 0;
  while (cnt < 10) {
    while (fb == ufb || !cdc[fb]) fb = (fb + 1) % 4;
    for (j = 0, k = sn; j < 2; j++, k = mi) {
      for (i = 0; i < 10; i++) {
        c = cards[10 * k + i];
        if (c == (fb << 3 | cd[fb][cdc[fb] - 1])) {
          swap(&cards[10 * k + i], &cards[10 * sn + cnt]);
          cnt++;
          cdc[fb]--;
          fb = (fb + 1) % 4;
          i = 10;
          j = 2;
        }
      }
    }
  }
}

int null_dicht(int sn, int handsp, int *skat, int *ufb, int *mfb, int *hfb) {
  int i, j, k, f, w, c, ok = 1, ncd[32];
  int sp, karten[40], hand[10], inhs[4][8];

  for (i = 0; i < 32; i++) {
    if (sn >= 0)
      ncd[i] = cards[i];
    else
      ncd[i] = i;
  }

  if (handsp) {
    for (i = 0; i < 2; i++) {
      c = skat[i];
      if (c >= 0) {
        f = c >> 3;
        w = c & 7;
        if (sn >= 0) {
          for (j = 0; j < 32; j++) {
            if (ncd[j] == c) {
              ncd[j] = ncd[sn * 10 + 8 + i];
              ncd[sn * 10 + 8 + i] = c;
              break;
            }
          }
        } else {
          ncd[30 + i] = c;
        }
      }
    }
  }

  for (k = 0; k < 3; k++) {
    sp = sn >= 0 ? (sn + k) % 3 : k;
    for (i = 0; i < 10; i++) {
      karten[k * 10 + i] = ncd[sp * 10 + i];
      hand[i] = ncd[sp * 10 + i];
      c = hand[i];
      f = c >> 3;
      w = c & 7;
    }

    for (i = 0; i < 4; i++) {
      for (j = 0; j < 8; j++) {
        inhs[i][j] = 0;
      }
    }

    for (i = 0; i < 10; i++) {
      c = hand[i];
      f = c >> 3;
      w = c & 7;
      inhs[f][w] = 1;
    }

    if (k == 0) {
      for (i = 0; i < 4; i++) {
        if (mfb) mfb[i] = 0;
        if (hfb) hfb[i] = 0;
      }

      for (i = 0; i < 10; i++) {
        c = hand[i];
        f = c >> 3;
        w = c & 7;
        if (w == AS) {
          if (mfb) mfb[f] = 1;
          ok = 0;
        }
        if (w == ZEHN) {
          if (hfb) hfb[f] = 1;
        }
      }

      if (ufb) {
        *ufb = -1;
        for (i = 0; i < 4; i++) {
          if (!inhs[i][AS] && inhs[i][ZEHN]) {
            *ufb = i;
            break;
          }
        }
      }
    }
  }

  return ok;
}